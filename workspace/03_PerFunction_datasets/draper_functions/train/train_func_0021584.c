process (GeglOperation       *op,
         void                *in_buf,
         void                *out_buf,
         glong                n_pixels,
         const GeglRectangle *roi,
         gint                 level)
{
  GeglChantO   *o         = GEGL_CHANT_PROPERTIES (op);
  gfloat       *in_pixel  = in_buf;
  gfloat       *out_pixel = out_buf;
  const gfloat *coeffs    = o->chant_data;

  in_pixel = in_buf;
  out_pixel = out_buf;

  if (! coeffs)
    {
      coeffs = o->chant_data = preprocess (o);
    }

  while (n_pixels--)
    {
      out_pixel[0] = in_pixel[0] * coeffs[0];
      out_pixel[1] = in_pixel[1] * coeffs[1];
      out_pixel[2] = in_pixel[2] * coeffs[2];
      out_pixel[3] = in_pixel[3];

      in_pixel += 4;
      out_pixel += 4;
    }

  return TRUE;
}
