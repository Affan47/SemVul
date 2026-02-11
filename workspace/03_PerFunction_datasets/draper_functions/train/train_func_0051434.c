default_icon_at_size (int width,
                      int height)
{

  GdkPixbuf *base;

  base = gdk_pixbuf_new_from_inline (-1, default_icon_data,
                                     FALSE,
                                     NULL);

  g_assert (base);

  if ((width < 0 && height < 0) ||
      (gdk_pixbuf_get_width (base) == width &&
       gdk_pixbuf_get_height (base) == height))
    {
      return base;
    }
  else
    {
      GdkPixbuf *scaled;

      scaled = gdk_pixbuf_scale_simple (base,
                                        width > 0 ? width :
                                        gdk_pixbuf_get_width (base),
                                        height > 0 ? height :
                                        gdk_pixbuf_get_height (base),
                                        GDK_INTERP_BILINEAR);

      g_object_unref (G_OBJECT (base));

      return scaled;
    }
}
