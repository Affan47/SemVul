vs_scanline_resample_linear_Y16 (uint8_t * dest, uint8_t * src, int src_width,
    int n, int *accumulator, int increment)
{
  int acc = *accumulator;
  int i;
  int j;
  int x;
  uint16_t *d = (uint16_t *) dest, *s = (uint16_t *) src;

  for (i = 0; i < n; i++) {
    j = acc >> 16;
    x = acc & 0xffff;

    if (j + 1 < src_width)
      d[i] = (s[j] * (65536 - x) + s[j + 1] * x) >> 16;
    else
      d[i] = s[j];

    acc += increment;
  }

  *accumulator = acc;
}
