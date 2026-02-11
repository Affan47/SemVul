PreconditionerFromPoints(const Mat &points, Mat3 *T) {
  Vec mean, variance;
  MeanAndVarianceAlongRows(points, &mean, &variance);

  double xfactor = sqrt(2.0 / variance(0));
  double yfactor = sqrt(2.0 / variance(1));


  if (variance(0) < 1e-8)
    xfactor = mean(0) = 1.0;
  if (variance(1) < 1e-8)
    yfactor = mean(1) = 1.0;

  *T << xfactor, 0,       -xfactor * mean(0),
        0,       yfactor, -yfactor * mean(1),
        0,       0,        1;
}
