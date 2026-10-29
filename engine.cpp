
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main() {
    // Step 1: Load the image
    cv::Mat image = cv::imread("clothing.png");

    if (image.empty()) {
        std::cout << "Error: Image not found!" << std::endl;
        return 1;
    }

    // Step 2: Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Step 3: Apply thresholding
    cv::Mat processed;
    cv::threshold(gray, processed, 0, 255,
                  cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Step 4: Initialize Tesseract OCR
    tesseract::TessBaseAPI ocr;

    if (ocr.Init(nullptr, "eng") != 0) {
        std::cout << "OCR initialization failed!"
                  << std::endl;
        return 1;
    }

    // Step 5: Pass the image to OCR
    ocr.SetImage(processed.data,
                 processed.cols,
                 processed.rows,
                 processed.channels(),
                 static_cast<int>(processed.step));

    // Step 6: Extract the text
    char* text = ocr.GetUTF8Text();

    if (text != nullptr) {
        std::cout << "Recognized Text:\n";
        std::cout << text << std::endl;

        delete[] text;
    }

    // Step 7: Clean up
    ocr.End();

    return 0;
}
