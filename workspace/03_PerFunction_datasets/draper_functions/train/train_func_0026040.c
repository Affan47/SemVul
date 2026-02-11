get_text_size(int *width, int *height,
		   enum client_font font, const char *text)
{
  PangoRectangle rect;

  if (!layout) {
    layout = pango_layout_new(gdk_pango_context_get());
  }

  pango_layout_set_font_description(layout, FONT(font));
  pango_layout_set_text(layout, text, -1);

  pango_layout_get_pixel_extents(layout, &rect, NULL);
  if (width) {
    *width = rect.width;
  }
  if (height) {
    *height = rect.height;
  }
}
