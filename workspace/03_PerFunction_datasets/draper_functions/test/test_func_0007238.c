__trunc (double x)
{
  int64_t i0, j0;
  int64_t sx;

  EXTRACT_WORDS64 (i0, x);
  sx = i0 & UINT64_C(0x8000000000000000);
  j0 = ((i0 >> 52) & 0x7ff) - 0x3ff;
  if (j0 < 52)
    {
      if (j0 < 0)

	INSERT_WORDS64 (x, sx);
      else
	INSERT_WORDS64 (x, sx | (i0 & ~(UINT64_C(0x000fffffffffffff) >> j0)));
    }
  else
    {
      if (j0 == 0x400)

	return x + x;
    }

  return x;
}
