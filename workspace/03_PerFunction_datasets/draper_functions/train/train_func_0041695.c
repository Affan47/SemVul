pixel_64_inline_2 (const a_pixel *s, int *d)
{
  int x, o;
  for (x = 320 / 64; x; --x) {
    a_pixel t1 = *s;
    int t;
    t = t1 | (t1 << 8) | (t1 << 16) | (t1 << 24);
    for (o = (200 % 64 - 1) * xbuf / 4; o >= 0; o -= xbuf / 4) {
      d[o + 0] = t;
      d[o + 1] = t;
      d[o + 2] = t;
      d[o + 3] = t;
      d[o + 4] = t;
      d[o + 5] = t;
      d[o + 6] = t;
      d[o + 7] = t;
      d[o + 8] = t;
      d[o + 9] = t;
      d[o + 10] = t;
      d[o + 11] = t;
      d[o + 12] = t;
      d[o + 13] = t;
      d[o + 14] = t;
      d[o + 15] = t;
    }
    s += 64;
    d += 16;
  }
}
