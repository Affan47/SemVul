a68g_atan2 (double x, double y)
{
  if (x == 0.0 && y == 0.0) {
    errno = EDOM;
    return (0.0);
  } else {
    BOOL_T flip = (BOOL_T) (y < 0.0);
    double z;
    y = ABS (y);
    if (x == 0.0) {
      z = A68_PI / 2.0;
    } else {
      BOOL_T flop = (BOOL_T) (x < 0.0);
      x = ABS (x);
      z = atan (y / x);
      if (flop) {
        z = A68_PI - z;
      }
    }
    if (flip) {
      z = -z;
    }
    return (z);
  }
}
