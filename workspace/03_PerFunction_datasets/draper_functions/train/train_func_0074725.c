gnac_ui_utils_add_border_to_pixbuf(GdkPixbuf *pixbuf)
{
  g_return_val_if_fail(GDK_IS_PIXBUF(pixbuf), NULL);

  gint width = gdk_pixbuf_get_width(pixbuf);
  gint height = gdk_pixbuf_get_height(pixbuf);
  GdkPixbuf *bordered = gdk_pixbuf_new(gdk_pixbuf_get_colorspace(pixbuf),
      gdk_pixbuf_get_has_alpha(pixbuf), gdk_pixbuf_get_bits_per_sample(pixbuf),
      width + (GNAC_UTILS_ICON_BORDER_WIDTH*2),
      height +(GNAC_UTILS_ICON_BORDER_WIDTH*2));
  gdk_pixbuf_fill(bordered, 0xff);
  gdk_pixbuf_copy_area(pixbuf, 0, 0, width, height, bordered,
      GNAC_UTILS_ICON_BORDER_WIDTH, GNAC_UTILS_ICON_BORDER_WIDTH);
  g_object_unref(pixbuf);
  return bordered;
}
