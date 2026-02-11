__logbf (float x)
{
  int32_t ix, rix;
  float ret;

  GET_FLOAT_WORD (ix, x);
  ix &= 0x7fffffff;
  if (ix == 0)
    return (float) -1.0 / fabsf (x);
  if (ix >= 0x7f800000)
    return x * x;
  if (__builtin_expect ((rix = ix >> 23) == 0, 0))
    {


      rix -= __builtin_clz (ix) - 9;
    }
  ret = (float) (rix - 127);

  return ret == -0.0 ? 0.0 : ret;
}
