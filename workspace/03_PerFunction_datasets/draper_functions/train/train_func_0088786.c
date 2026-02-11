__ieee754_yn (int n, double x)
{
  int32_t i, hx, ix, lx;
  int32_t sign;
  double a, b, temp;

  EXTRACT_WORDS (hx, lx, x);
  ix = 0x7fffffff & hx;

  if (__builtin_expect ((ix | ((u_int32_t) (lx | -lx)) >> 31) > 0x7ff00000, 0))
    return x + x;
  if (__builtin_expect ((ix | lx) == 0, 0))
    return -HUGE_VAL + x;
  ;
  if (__builtin_expect (hx < 0, 0))
    return zero / (zero * x);
  sign = 1;
  if (n < 0)
    {
      n = -n;
      sign = 1 - ((n & 1) << 1);
    }
  if (n == 0)
    return (__ieee754_y0 (x));
  if (n == 1)
    return (sign * __ieee754_y1 (x));
  if (__builtin_expect (ix == 0x7ff00000, 0))
    return zero;
  if (ix >= 0x52D00000)
    {


      double c;
      double s;
      __sincos (x, &s, &c);
      switch (n & 3)
	{
	case 0: temp = s - c; break;
	case 1: temp = -s - c; break;
	case 2: temp = -s + c; break;
	case 3: temp = s + c; break;
	}
      b = invsqrtpi * temp / __ieee754_sqrt (x);
    }
  else
    {
      u_int32_t high;
      a = __ieee754_y0 (x);
      b = __ieee754_y1 (x);

      GET_HIGH_WORD (high, b);
      for (i = 1; i < n && high != 0xfff00000; i++)
	{
	  temp = b;
	  b = ((double) (i + i) / x) * b - a;
	  GET_HIGH_WORD (high, b);
	  a = temp;
	}

      if (!__finite (b))
	__set_errno (ERANGE);
    }
  if (sign > 0)
    return b;
  else
    return -b;
}
