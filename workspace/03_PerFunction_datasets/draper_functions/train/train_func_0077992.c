double_int_sext (double_int cst, unsigned prec)
{
  double_int mask = double_int_mask (prec);
  double_int r;
  unsigned HOST_WIDE_INT snum;

  if (prec <= HOST_BITS_PER_WIDE_INT)
    snum = cst.low;
  else
    {
      prec -= HOST_BITS_PER_WIDE_INT;
      snum = (unsigned HOST_WIDE_INT) cst.high;
    }
  if (((snum >> (prec - 1)) & 1) == 1)
    {
      r.low = cst.low | ~mask.low;
      r.high = cst.high | ~mask.high;
    }
  else
    {
      r.low = cst.low & mask.low;
      r.high = cst.high & mask.high;
    }

  return r;
}
