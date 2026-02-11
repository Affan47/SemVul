webx_preview_create_background (GdkPixbuf *src)
{
  GdkPixbuf    *dst;
  guchar       *pixels;
  guchar       *row;
  gint          rowstride;
  gint          width;
  gint          height;
  gint          i;
  gint          j;
  gboolean      has_alpha;

  dst = gdk_pixbuf_copy (src);

  pixels    = gdk_pixbuf_get_pixels (dst);
  width     = gdk_pixbuf_get_width (dst);
  height    = gdk_pixbuf_get_height (dst);
  rowstride = gdk_pixbuf_get_rowstride (dst);
  has_alpha = gdk_pixbuf_get_has_alpha (dst);

  for (i = 0; i < height; i++)
    {
      row = pixels;
      for (j = 0; j < width; j++)
        {
          *row = *row / 4 + 127;
          row++;
          *row = *row / 4 + 127;
          row++;
          *row = *row / 4 + 127;
          row++;
          if (has_alpha)
            row++;
        }
      pixels += rowstride;
    }

  return dst;
}
