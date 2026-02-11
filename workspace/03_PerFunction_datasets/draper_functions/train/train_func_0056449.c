__exp10 (double x)
{
  double z = __ieee754_exp10 (x);
  if (__builtin_expect (!__finite (z) || z == 0, 0)
      && __finite (x) && _LIB_VERSION != _IEEE_)

    return __kernel_standard (x, x, 46 + !!__signbit (x));

  return z;
}
