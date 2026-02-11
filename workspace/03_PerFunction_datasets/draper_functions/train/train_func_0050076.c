zoom (GstRadioacTV * filter)
{
  gint b, x, y;
  guint8 *p, *q;
  gint blocks, height;
  gint dx;

  p = filter->blurzoombuf + filter->buf_area;
  q = filter->blurzoombuf;
  height = filter->buf_height;
  blocks = filter->buf_width_blocks;

  for (y = 0; y < height; y++) {
    p += filter->blurzoomy[y];
    for (b = 0; b < blocks; b++) {
      dx = filter->blurzoomx[b];
      for (x = 0; x < 32; x++) {
        p += (dx & 1);
        *q++ = *p;
        dx = dx >> 1;
      }
    }
  }
}
