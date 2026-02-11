colorize_pixbuf (GdkPixbuf *orig,
                 GdkRGBA   *new_color)
{
  GdkPixbuf *pixbuf;
  double intensity;
  int x, y;
  const guchar *src;
  guchar *dest;
  int orig_rowstride;
  int dest_rowstride;
  int width, height;
  gboolean has_alpha;
  const guchar *src_pixels;
  guchar *dest_pixels;

  pixbuf = gdk_pixbuf_new (gdk_pixbuf_get_colorspace (orig), gdk_pixbuf_get_has_alpha (orig),
			   gdk_pixbuf_get_bits_per_sample (orig),
			   gdk_pixbuf_get_width (orig), gdk_pixbuf_get_height (orig));

  if (pixbuf == NULL)
    return NULL;

  orig_rowstride = gdk_pixbuf_get_rowstride (orig);
  dest_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);
  has_alpha = gdk_pixbuf_get_has_alpha (orig);
  src_pixels = gdk_pixbuf_get_pixels (orig);
  dest_pixels = gdk_pixbuf_get_pixels (pixbuf);

  for (y = 0; y < height; y++)
    {
      src = src_pixels + y * orig_rowstride;
      dest = dest_pixels + y * dest_rowstride;

      for (x = 0; x < width; x++)
        {
          double dr, dg, db;

          intensity = INTENSITY (src[0], src[1], src[2]) / 255.0;

          if (intensity <= 0.5)
            {

              dr = new_color->red * intensity * 2.0;
              dg = new_color->green * intensity * 2.0;
              db = new_color->blue * intensity * 2.0;
            }
          else
            {

              dr = new_color->red + (1.0 - new_color->red) * (intensity - 0.5) * 2.0;
              dg = new_color->green + (1.0 - new_color->green) * (intensity - 0.5) * 2.0;
              db = new_color->blue + (1.0 - new_color->blue) * (intensity - 0.5) * 2.0;
            }

          dest[0] = CLAMP_UCHAR (255 * dr);
          dest[1] = CLAMP_UCHAR (255 * dg);
          dest[2] = CLAMP_UCHAR (255 * db);

          if (has_alpha)
            {
              dest[3] = src[3];
              src += 4;
              dest += 4;
            }
          else
            {
              src += 3;
              dest += 3;
            }
        }
    }

  return pixbuf;
}
