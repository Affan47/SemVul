ar_svg_render_cairo_sub (ArSvg *svg,
                                 cairo_t *cr,
                                 const char *node,
                                 int width,
                                 int height,
                                 double xoffset,
                                 double yoffset,
                                 double xzoom,
                                 double yzoom)
{
  cairo_matrix_t matrix;

  g_return_if_fail (AR_IS_SVG (svg));

  if (svg->font_options) {
    cairo_set_antialias (cr, cairo_font_options_get_antialias (svg->font_options));

    cairo_set_font_options (cr, svg->font_options);
  }

  cairo_matrix_init_identity (&matrix);
  cairo_matrix_scale (&matrix, xzoom, yzoom);
  cairo_matrix_translate (&matrix, xoffset, yoffset);

  cairo_set_matrix (cr, &matrix);

  rsvg_handle_render_cairo_sub (RSVG_HANDLE (svg), cr, node);
}
