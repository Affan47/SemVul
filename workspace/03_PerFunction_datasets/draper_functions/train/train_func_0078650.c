color_correct(double corr)
{
  const int palettesize = palette.size();
  if (palettesize > 0)
    {

      int i;
      GTArray<GPixel> pix(0,palettesize-1);
      GPixel *r = pix;
      PColor *q = palette;
      for (i=0; i<palettesize; i++)
        {
          r[i].b = q[i].p[0];
          r[i].g = q[i].p[1];
          r[i].r = q[i].p[2];
        }

      GPixmap::color_correct(corr, r, palettesize);

      for (i=0; i<palettesize; i++)
        {
          q[i].p[0] = r[i].b;
          q[i].p[1] = r[i].g;
          q[i].p[2] = r[i].r;
        }
    }
}
