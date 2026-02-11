windchillTemperature(double t, double ff, double missval)
{
  static const double tmax = 33.0;
  static const double vmin = 1.39;

  return ff < vmin || t > tmax ? missval : tmax + (t - tmax) * (0.478 + 0.237 * (sqrt(ff * 3.6) - 0.0124 * ff * 3.6));
}
