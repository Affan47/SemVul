copy_from_partial(int w, int h,
                  const GPixel *s, int sadd, int xmin, int xmax, int ymin, int ymax,
                  GPixel *d, int dadd)
{
  int y = 0;
  s += (ymin>0 ? sadd * ymin : 0);
  while (y<ymin  && y<h)
    {
      copy_line(s, xmin, xmax, d, 0, w);
      y += 1;
      d += dadd;
    }
  while (y<ymax && y<h)
    {
      copy_line(s, xmin, xmax, d, 0, w);
      y += 1;
      s += sadd;
      d += dadd;
    }
  s -= sadd;
  while (y < h)
    {
      copy_line(s, xmin, xmax, d, 0, w);
      y += 1;
      d += dadd;
    }
}
