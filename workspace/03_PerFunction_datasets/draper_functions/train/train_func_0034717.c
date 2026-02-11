write_scaled(cv::Mat &color, cv::Mat &alpha, cv::Rect targetROI) const
{
  cv::Mat scaled_color, scaled_alpha;
  cv::Size scaled_size(targetROI.width, targetROI.height);
  cv::Rect roi(cv::Point(0, 0), scaled_size);


  cv::resize(mColor, scaled_color, scaled_size, 1.0, 1.0, cv::INTER_CUBIC);
  cv::resize(mAlpha, scaled_alpha, scaled_size, 1.0, 1.0, cv::INTER_CUBIC);

  if (targetROI.x < 0) {

    roi.x += std::abs(targetROI.x);
    roi.width -= std::abs(targetROI.x);
    targetROI.width -= std::abs(targetROI.x);
    targetROI.x = 0;
  }
  if (targetROI.x >= color.cols) {
    std::cerr << "target roi is not in image: " << targetROI << std::endl;
    return;
  } else if ((targetROI.x + targetROI.width) >= color.cols) {

    int overlap = (targetROI.x + targetROI.width) - color.cols;
    roi.width -= overlap;
    targetROI.width -= overlap;
  }

  if (targetROI.y < 0) {

    roi.y += std::abs(targetROI.y);
    roi.height -= std::abs(targetROI.y);
    targetROI.height -= std::abs(targetROI.y);
    targetROI.y = 0;
  }
  if (targetROI.y >= color.rows) {
    std::cerr << "target roi is not in image: " << targetROI << std::endl;
    return;
  } else if ((targetROI.y + targetROI.height) >= color.rows) {

    int overlap = (targetROI.y + targetROI.height) - color.rows;
    roi.height -= overlap;
    targetROI.height -= overlap;
  }

  for (int x = 0; x < targetROI.width; x++) {
    for (int y = 0; y < targetROI.height; y++) {
      if (scaled_alpha(roi).at<uchar>(y, x) != 0) {
        alpha(targetROI).at<uchar>(y, x) = scaled_alpha(roi).at<uchar>(y, x);
        color(targetROI).at<cv::Vec3b>(y, x) = scaled_color(roi).at<cv::Vec3b>(y, x);
      }
    }
  }
}
