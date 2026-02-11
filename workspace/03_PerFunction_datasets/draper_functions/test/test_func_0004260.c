__llround (double x)
{
  int32_t j0;
  int64_t i0;
  long long int result;
  int sign;

  EXTRACT_WORDS64 (i0, x);
  j0 = ((i0 >> 52) & 0x7ff) - 0x3ff;
  sign = i0 < 0 ? -1 : 1;
  i0 &= UINT64_C(0xfffffffffffff);
  i0 |= UINT64_C(0x10000000000000);

  if (j0 < (int32_t) (8 * sizeof (long long int)) - 1)
    {
      if (j0 < 0)
	return j0 < -1 ? 0 : sign;
      else if (j0 >= 52)
	result = i0 << (j0 - 52);
      else
	{
	  i0 += UINT64_C(0x8000000000000) >> j0;

	  result = i0 >> (52 - j0);
	}
    }
  else
    {


      return (long long int) x;
    }

  return sign * result;
}
