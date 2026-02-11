gst_cairo_render_push_surface (GstCairoRender * c, cairo_surface_t * surface)
{
  cairo_status_t s = 0;
  cairo_t *cr;

  if (!c->surface) {
    s = cairo_surface_write_to_png_stream (surface, write_func, c);
    cairo_surface_destroy (surface);
    if (s != CAIRO_STATUS_SUCCESS) {
      GST_DEBUG_OBJECT (c, "Could not create PNG stream: %s.",
          cairo_status_to_string (s));
      return FALSE;
    }
    return TRUE;
  }

  cr = cairo_create (c->surface);
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
  cairo_show_page (cr);
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  return (TRUE);
}
