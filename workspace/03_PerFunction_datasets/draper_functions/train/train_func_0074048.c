trailing_zeros () const
{
  const double_int &a = *this;
  unsigned HOST_WIDE_INT w = a.low ? a.low : (unsigned HOST_WIDE_INT) a.high;
  unsigned bits = a.low ? 0 : HOST_BITS_PER_WIDE_INT;
  if (!w)
    return HOST_BITS_PER_DOUBLE_INT;
  bits += ctz_hwi (w);
  return bits;
}
