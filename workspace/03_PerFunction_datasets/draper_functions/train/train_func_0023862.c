process (GeglOperation       *operation,
         void                *out_buf,
         glong                n_pixels,
         const GeglRectangle *roi,
         gint                 level)
{
  GeglChantO *o = GEGL_CHANT_PROPERTIES (operation);
  gfloat     *out_pixel = out_buf;
  gint        x = roi->x;
  gint        y = roi->y;


  while (n_pixels--)
    {
      gfloat val;

      val = PerlinNoise3D ((double) (x)/50.0,
                           (double) (y)/50.0,
                           (double) o->zoff, o->alpha, o->scale,
                           o->n);
      *out_pixel = val * 0.5 + 0.5;
      out_pixel ++;


      x++;
      if (x>=roi->x + roi->width)
        {
          x=roi->x;
          y++;
        }
    }
  return  TRUE;
}
