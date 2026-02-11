downscale_float (gint    components,
                 gint    width,
                 gint    height,
                 gint    rowstride,
                 guchar *src_data,
                 guchar *dst_data)
{
  gint y;

  if (!src_data || !dst_data)
    return;
  for (y = 0; y < height / 2; y++)
    {
      gint    x;
      gfloat *dst = (gfloat *) (dst_data + y * rowstride);
      gfloat *src = (gfloat *) (src_data + y * 2 * rowstride);

      for (x = 0; x < width / 2; x++)
        {
          int i;
          for (i = 0; i < components; i++)
            dst[i] = (src[i] +
                      src[i + components] +
                      src[i + (width * components)] +
                      src[i + (width + 1) * components]) /
                     4.0;

          dst += components;
          src += components * 2;
        }
    }
}
