can_mul_int(const int x, const int y) {
  if (x > 0) {
    if (y >= 0)
      return y <= div(INT_MAX, x).quot;
    else
      return y >= div(INT_MIN, x).quot;
  } else if (x < 0) {
    if (y >= 0)
      return y <= div(INT_MIN, x).quot;
    else
      return y >= div(INT_MAX, x).quot;
  } else
    return 1;
}
