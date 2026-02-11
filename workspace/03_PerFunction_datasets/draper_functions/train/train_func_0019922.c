ComputeUndistortedCoordinates(
    const PinholeCamera &camera,
    const Vec2 &point,
    Vec2 *undistorted_point) const {
  Vec2 point_centered = point - camera.principal_point();

  double u = point_centered.x() / camera.focal_x();
  double v = point_centered.y() / camera.focal_y();
  double radius_squared = u * u + v * v;

  double coef_radial = 0;
  if (radial_distortion_.size() > 0) {
    for (int i = radial_distortion_.size() - 1; i >= 0; --i) {
      coef_radial = (coef_radial + radial_distortion_[i]) * radius_squared;
    }
  }

  undistorted_point->x() = point.x() + point_centered.x() * coef_radial;
  undistorted_point->y() = point.y() + point_centered.y() * coef_radial;

  if (tangential_distortion_.size() >= 2) {
    double coef_tangential = 1;

    for (size_t i = 2; i < tangential_distortion_.size(); ++i) {
      coef_tangential += tangential_distortion_[i] * radius_squared;
    }
    undistorted_point->x() += (tangential_distortion_.x() * (radius_squared +
                               2. * u * u) + 2. * tangential_distortion_.y() *
                               u * v) * coef_tangential;
    undistorted_point->y() += (tangential_distortion_.y() * (radius_squared +
                               2. * v * v) + 2. * tangential_distortion_.x() *
                               u * v) * coef_tangential;
  }
}
