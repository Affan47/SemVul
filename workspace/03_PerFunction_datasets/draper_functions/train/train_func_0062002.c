lshift_double (unsigned HOST_WIDE_INT l1, HOST_WIDE_INT h1,
	       HOST_WIDE_INT count, unsigned int prec,
	       unsigned HOST_WIDE_INT *lv, HOST_WIDE_INT *hv, bool arith)
{
  unsigned HOST_WIDE_INT signmask;

  if (count < 0)
    {
      rshift_double (l1, h1, absu_hwi (count), prec, lv, hv, arith);
      return;
    }

  if (SHIFT_COUNT_TRUNCATED)
    count %= prec;

  if (count >= HOST_BITS_PER_DOUBLE_INT)
    {


      *hv = 0;
      *lv = 0;
    }
  else if (count >= HOST_BITS_PER_WIDE_INT)
    {
      *hv = l1 << (count - HOST_BITS_PER_WIDE_INT);
      *lv = 0;
    }
  else
    {
      *hv = (((unsigned HOST_WIDE_INT) h1 << count)
	     | (l1 >> (HOST_BITS_PER_WIDE_INT - count - 1) >> 1));
      *lv = l1 << count;
    }


  signmask = -((prec > HOST_BITS_PER_WIDE_INT
		? ((unsigned HOST_WIDE_INT) *hv
		   >> (prec - HOST_BITS_PER_WIDE_INT - 1))
		: (*lv >> (prec - 1))) & 1);

  if (prec >= HOST_BITS_PER_DOUBLE_INT)
    ;
  else if (prec >= HOST_BITS_PER_WIDE_INT)
    {
      *hv &= ~((HOST_WIDE_INT) (-1) << (prec - HOST_BITS_PER_WIDE_INT));
      *hv |= signmask << (prec - HOST_BITS_PER_WIDE_INT);
    }
  else
    {
      *hv = signmask;
      *lv &= ~((unsigned HOST_WIDE_INT) (-1) << prec);
      *lv |= signmask << prec;
    }
}
