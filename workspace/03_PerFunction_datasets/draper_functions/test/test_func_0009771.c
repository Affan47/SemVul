Power(unsigned x, unsigned n)
{
  unsigned xn, xp;

  if (n == 0 || x == 1)
    return 1;

  if (x == 0)
    return 0;

  if (n >= sizeof(unsigned) * 8)
    return INTERVAL_MAX_INTEGER;

  xn = 1;
  xp = x;

  while (n)
    {
      if (n & 1)
	xn *= xp;
      xp *= xp;
      n >>= 1;
    }

  return ((long) xn > 0 && (long) xn <= INTERVAL_MAX_INTEGER)
    ? xn : INTERVAL_MAX_INTEGER;
}
