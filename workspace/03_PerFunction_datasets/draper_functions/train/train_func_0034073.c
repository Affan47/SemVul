vs_scanline_resample_nearest_AYUV64 (uint8_t * dest8, uint8_t * src8,
    int src_width, int n, int *accumulator, int increment)
{
  guint16 *dest = (guint16 *) dest8;
  guint16 *src = (guint16 *) src8;
  int acc = *accumulator;
  int i;
  int j;
  int x;

  for (i = 0; i < n; i++) {
    j = acc >> 16;
    x = acc & 0xffff;
    dest[i * 4 + 0] = (x < 32768
        || j + 1 >= src_width) ? src[j * 4 + 0] : src[j * 4 + 4];
    dest[i * 4 + 1] = (x < 32768
        || j + 1 >= src_width) ? src[j * 4 + 1] : src[j * 4 + 5];
    dest[i * 4 + 2] = (x < 32768
        || j + 1 >= src_width) ? src[j * 4 + 2] : src[j * 4 + 6];
    dest[i * 4 + 3] = (x < 32768
        || j + 1 >= src_width) ? src[j * 4 + 3] : src[j * 4 + 7];

    acc += increment;
  }

  *accumulator = acc;
}
