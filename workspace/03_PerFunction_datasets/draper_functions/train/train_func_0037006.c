a68g_acosh (double x)
{
  if (x > 1.0 / sqrt (DBL_EPSILON)) {
    return (log (x) + log (2.0));
  } else if (x > 2.0) {
    return (log (2.0 * x - 1.0 / (sqrt (x * x - 1.0) + x)));
  } else if (x > 1.0) {
    double t = x - 1.0;
    return (a68g_log1p (t + sqrt (2.0 * t + t * t)));
  } else if (x == 1.0) {
    return (0.0);
  } else {
    errno = EDOM;
    return (0.0);
  }
}
