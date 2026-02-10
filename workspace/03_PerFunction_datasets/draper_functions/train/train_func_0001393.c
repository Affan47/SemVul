canvas_put_text(struct canvas *pcanvas, int canvas_x, int canvas_y,
		     enum client_font font,
		     struct color *pcolor,
		     const char *text)
{
  cairo_t *cr;

  if (!layout) {
    layout = pango_layout_new(gdk_pango_context_get_for_screen(gdk_screen_get_default()));
  }

  if (!pcanvas->drawable) {
    cr = cairo_create(pcanvas->surface);
  } else {
    cr = pcanvas->drawable;
  }

  if (pcanvas->drawable) {
    cairo_save(cr);
  }

  pango_layout_set_font_description(layout, FONT(font));
  pango_layout_set_text(layout, text, -1);

  if (fonts[font].shadowed) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, canvas_x + 1, canvas_y + 1);
    pango_cairo_show_layout (cr, layout);
  }

  cairo_move_to(cr, canvas_x, canvas_y);
  gdk_cairo_set_source_rgba(cr, &pcolor->color);
  pango_cairo_show_layout(cr, layout);

  if (!pcanvas->drawable) {
    cairo_destroy(cr);
  } else {
    cairo_restore(cr);
  }
}
