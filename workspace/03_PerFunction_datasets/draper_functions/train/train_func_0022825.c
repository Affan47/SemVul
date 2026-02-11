readBits(int n, Stream *str)
{
  Guint bit, bits;

  if (n < 0) return -1;
  if (n == 0) return 0;

  if (n == 1)
    return readBit(str);

  bit = (readBit(str) << (n-1));
  if (bit == (Guint) -1)
    return -1;

  bits = readBits(n-1, str);
  if (bits == (Guint) -1)
    return -1;

  return bit | bits;
}
