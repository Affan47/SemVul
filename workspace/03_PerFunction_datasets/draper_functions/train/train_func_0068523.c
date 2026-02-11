crc32_unsigned_bits (unsigned chksum, unsigned value, unsigned bits)
{
  unsigned ix;

  for (ix = bits; ix--; value <<= 1)
    {
      unsigned feedback;

      feedback = (value ^ chksum) & 0x80000000 ? 0x04c11db7 : 0;
      chksum <<= 1;
      chksum ^= feedback;
    }
  return chksum;
}
