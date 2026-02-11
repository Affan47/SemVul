replicate_rows (GdkPixbuf  *src,
                int         src_x,
                int         src_y,
                int         width,
                int         height)
{
  unsigned int n_channels = gdk_pixbuf_get_n_channels (src);
  unsigned int src_rowstride = gdk_pixbuf_get_rowstride (src);
  unsigned char *pixels = (gdk_pixbuf_get_pixels (src) + src_y * src_rowstride + src_x
                           * n_channels);
  unsigned char *dest_pixels;
  GdkPixbuf *result;
  unsigned int dest_rowstride;
  int i;

  result = gdk_pixbuf_new (GDK_COLORSPACE_RGB, n_channels == 4, 8,
                           width, height);
  dest_rowstride = gdk_pixbuf_get_rowstride (result);
  dest_pixels = gdk_pixbuf_get_pixels (result);

  for (i = 0; i < height; i++)
    memcpy (dest_pixels + dest_rowstride * i, pixels, n_channels * width);

  return result;
}
