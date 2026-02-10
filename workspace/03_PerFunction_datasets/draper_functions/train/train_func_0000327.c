vs_scanline_resample_nearest_AYUV64 (uint8_t * dest8, uint8_t * src8,
    int src_width, int n, int *accumulator, int increment)
{
  guint16 *dest = (guint16 *) dest8;
  guint16 *src = (guint16 *) src8;
  int acc = *accumulator;
  int i, j;

  for (i = 0; i < n; i++) {
    j = (acc + 0x8000) >> 16;

    dest[i * 4 + 0] = src[j * 4 + 0];
    dest[i * 4 + 1] = src[j * 4 + 1];
    dest[i * 4 + 2] = src[j * 4 + 2];
    dest[i * 4 + 3] = src[j * 4 + 3];

    acc += increment;
  }

  *accumulator = acc;
}
