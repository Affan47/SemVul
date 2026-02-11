vs_scanline_merge_linear_Y16 (uint8_t * dest, uint8_t * src1, uint8_t * src2,
    int n, int x)
{
  uint16_t *d = (uint16_t *) dest;
  const uint16_t *s1 = (const uint16_t *) src1;
  const uint16_t *s2 = (const uint16_t *) src2;

  if (x == 0) {
    memcpy (d, s1, n * 2);
  } else {
    orc_merge_linear_u16 (d, s1, s2, 65536 - x, x, n);
  }
}
