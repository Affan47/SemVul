a68g_atanh (double x)
{
  double a = ABS (x);
  double s = (double) (x < 0 ? -1 : 1);
  if (a >= 1.0) {
    errno = EDOM;
    return (0.0);
  } else if (a >= 0.5) {
    return (s * 0.5 * a68g_log1p (2 * a / (1.0 - a)));
  } else if (a > DBL_EPSILON) {
    return (s * 0.5 * a68g_log1p (2.0 * a + 2.0 * a * a / (1.0 - a)));
  } else {
    return (x);
  }
}
