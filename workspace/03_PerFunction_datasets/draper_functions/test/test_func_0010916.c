bit_set(unsigned char* bits, int pos, int bit)
{
  unsigned char filter = 1 << (7 - (pos & 0x7));
  if (bit == 0) {
    return bits[pos >> 3] &= ~filter;
  } else {
    return bits[pos >> 3] |= filter;
  }
}
