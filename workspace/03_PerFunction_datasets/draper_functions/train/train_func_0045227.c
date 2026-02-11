ApplyTransformationToPoints(const Mat &points,
                                 const Mat3 &T,
                                 Mat *transformed_points) {
  int n = points.cols();
  transformed_points->resize(2,n);
  Mat3X p(3, n);
  EuclideanToHomogeneous(points, &p);
  p = T * p;
  HomogeneousToEuclidean(p, transformed_points);
}
