makeKp3d(std::vector<cv::KeyPoint> kp) {
  std::vector<cv::KeyPoint3D> kp_3d;
  kp_3d.reserve(kp.size());
  for (size_t i = 0; i < kp.size(); i++) {
    kp_3d.push_back(kp[i]);
  }
  return kp_3d;
}
