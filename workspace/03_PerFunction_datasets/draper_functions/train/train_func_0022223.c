pow(const Real& r, unsigned long n) {
  if (n == 0)
    return Real(1);
  else if (n == 1)
    return r;
  else {
    Real x = r;
    while ((n % 2) == 0) {
      x *= x;
      n >>= 1;
    }
    Real u = x;
    while (true) {
      n >>= 1;
      if (n == 0)
        return u;
      x *= x;
      if ((n % 2) == 1)
        u *= x;
    }
    return u;
  }
}
