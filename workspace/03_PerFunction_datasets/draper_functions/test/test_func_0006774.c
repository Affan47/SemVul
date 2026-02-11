__llroundf (float x)
{
  int32_t j0;
  u_int32_t i;
  long long int result;
  int sign;

  GET_FLOAT_WORD (i, x);
  j0 = ((i >> 23) & 0xff) - 0x7f;
  sign = (i & 0x80000000) != 0 ? -1 : 1;
  i &= 0x7fffff;
  i |= 0x800000;

  if (j0 < (int32_t) (8 * sizeof (long long int)) - 1)
    {
      if (j0 < 0)
	return j0 < -1 ? 0 : sign;
      else if (j0 >= 23)
	result = (long long int) i << (j0 - 23);
      else
	{
	  i += 0x400000 >> j0;

	  result = i >> (23 - j0);
	}
    }
  else
    {


      return (long long int) x;
    }

  return sign * result;
}
