vs_scanline_merge_4tap_AYUV64 (uint16_t * dest, uint16_t * src1,
    uint16_t * src2, uint16_t * src3, uint16_t * src4, int n, int acc)
{
  int i;
  int y;
  int off;
  int a, b, c, d;

  acc = (acc >> 8) & 0xff;
  a = vs_4tap_taps[acc][0];
  b = vs_4tap_taps[acc][1];
  c = vs_4tap_taps[acc][2];
  d = vs_4tap_taps[acc][3];
  for (i = 0; i < n; i++) {
    for (off = 0; off < 4; off++) {
      y = a * src1[i * 4 + off];
      y += b * src2[i * 4 + off];
      y += c * src3[i * 4 + off];
      y += d * src4[i * 4 + off];
      y += (1 << (SHIFT - 1));
      dest[i * 4 + off] = CLAMP (y >> SHIFT, 0, 65535);
    }
  }
}
