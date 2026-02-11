get_surface_size (cairo_scaled_font_t *scaled_font,
				double *w, double *h)
{
  cairo_font_extents_t font_extents;

  cairo_scaled_font_extents (scaled_font, &font_extents);

  bool vertical = HB_DIRECTION_IS_VERTICAL (direction);
  (vertical ? *w : *h) = (int) lines->len * (font_extents.height + view_options.line_space) - view_options.line_space;
  (vertical ? *h : *w) = 0;
  for (unsigned int i = 0; i < lines->len; i++) {
    helper_cairo_line_t &line = g_array_index (lines, helper_cairo_line_t, i);
    double x_advance, y_advance;
    line.get_advance (&x_advance, &y_advance);
    if (vertical)
      *h =  MAX (*h, y_advance);
    else
      *w =  MAX (*w, x_advance);
  }

  *w += view_options.margin.l + view_options.margin.r;
  *h += view_options.margin.t + view_options.margin.b;
}
