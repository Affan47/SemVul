convert_yca_to_rgba (GeglBuffer *buf,
                     gint        has_alpha,
                     const V3f  &yw)
{
  gchar *pixels;
  gfloat r,g,b, y, ry, by, *pxl;
  gint row, i, dx = has_alpha ? 4 : 3;
  GeglRectangle rect;
  gint pxsize;
  g_object_get (buf, "px-size", &pxsize, NULL);

  pixels = (gchar*) g_malloc0 (gegl_buffer_get_width (buf) * pxsize);

  for (row=0; row<gegl_buffer_get_height (buf); row++)
    {
      gegl_rectangle_set (&rect, 0, row, gegl_buffer_get_width (buf), 1);
      gegl_buffer_get (buf, &rect, 1.0, NULL, pixels, GEGL_AUTO_ROWSTRIDE,
                       GEGL_ABYSS_NONE);
      pxl = (gfloat*) pixels;

      for (i=0; i<gegl_buffer_get_width (buf); i++)
        {
          y  = pxl[0];
          ry = pxl[1];
          by = pxl[2];

          r = y*(ry+1.0);
          b = y*(by+1.0);
          g = (y - r*yw.x - b*yw.z) / yw.y;

          pxl[0] = r;
          pxl[1] = g;
          pxl[2] = b;

          pxl += dx;
        }

      gegl_buffer_set (buf, &rect, 0, NULL, pixels, GEGL_AUTO_ROWSTRIDE);
    }

  g_free (pixels);
}
