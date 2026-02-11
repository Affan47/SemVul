bng_leading_zero_bits(bngdigit d)
{
  int n = BNG_BITS_PER_DIGIT;
#ifdef ARCH_SIXTYFOUR
  if ((d & 0xFFFFFFFF00000000L) != 0) { n -= 32; d = d >> 32; }
#endif
  if ((d & 0xFFFF0000) != 0) { n -= 16; d = d >> 16; }
  if ((d & 0xFF00) != 0) { n -= 8; d = d >> 8; }
  if ((d & 0xF0) != 0) { n -= 4; d = d >> 4; }
  if ((d & 0xC) != 0) { n -= 2; d = d >> 2; }
  if ((d & 2) != 0) { n -= 1; d = d >> 1; }
  return n - d;
}
