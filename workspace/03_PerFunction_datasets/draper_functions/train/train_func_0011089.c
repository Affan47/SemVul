c2g (GeglBuffer          *src,
                 const GeglRectangle *src_rect,
                 GeglBuffer          *dst,
                 const GeglRectangle *dst_rect,
                 gint                 radius,
                 gint                 samples,
                 gint                 iterations,
                 gdouble              rgamma)
{
  gint x,y;
  gint    dst_offset=0;
  gfloat *src_buf;
  gfloat *dst_buf;
  gint    inw = src_rect->width;
  gint    outw = dst_rect->width;
  gint    inh = src_rect->height;

  src_buf = g_new0 (gfloat, src_rect->width * src_rect->height * 4);
  dst_buf = g_new0 (gfloat, dst_rect->width * dst_rect->height * 2);

  gegl_buffer_get (src, src_rect, 1.0, babl_format ("RGBA float"), src_buf, GEGL_AUTO_ROWSTRIDE,
                   GEGL_ABYSS_NONE);

  for (y=radius; y<dst_rect->height+radius; y++)
    {
      gint src_offset = (inw*y+radius)*4;
      for (x=radius; x<outw+radius; x++)
        {
          gfloat *pixel= src_buf + src_offset;
          gfloat  min[4];
          gfloat  max[4];

          compute_envelopes (src_buf,
                             inw, inh,
                             x, y,
                             radius, samples,
                             iterations,
                             FALSE,
                             rgamma,
                             min, max);
          {


            gfloat nominator = 0;
            gfloat denominator = 0;
            gint c;
            for (c=0; c<3; c++)
              {
                nominator   += (pixel[c] - min[c]) * (pixel[c] - min[c]);
                denominator += (pixel[c] - max[c]) * (pixel[c] - max[c]);
              }

            nominator = sqrt (nominator);
            denominator = sqrt (denominator);
            denominator = nominator + denominator;

            if (denominator>0.000)
              {
                dst_buf[dst_offset+0] = nominator/denominator;
              }
            else
              {

                dst_buf[dst_offset+0] = 0.5;
              }
            dst_buf[dst_offset+1] = src_buf[src_offset+3];

            src_offset+=4;
            dst_offset+=2;
          }
        }
    }
  gegl_buffer_set (dst, dst_rect, 0, babl_format ("YA float"), dst_buf, GEGL_AUTO_ROWSTRIDE);
  g_free (src_buf);
  g_free (dst_buf);
}
