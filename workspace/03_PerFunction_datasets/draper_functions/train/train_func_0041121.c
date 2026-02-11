clLg(unsigned long x) {
  if (x > (ULONG_MAX >> 1))
    return LONG_BIT;
  if (x >= 2)
    return flrLg((x << 1) - 1);

  if (x == 1)
    return 0;
  return -1;
}
