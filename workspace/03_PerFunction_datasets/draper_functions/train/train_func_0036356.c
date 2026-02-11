o_pin_draw_place (GSCHEM_TOPLEVEL *w_current, int dx, int dy, OBJECT *o_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int size = 0;

  if (o_current->line == NULL) {
    return;
  }

  if (toplevel->pin_style == THICK)
    size = o_current->line_width;

  gschem_cairo_line (w_current, END_NONE, size,
                     o_current->line->x[0] + dx, o_current->line->y[0] + dy,
                     o_current->line->x[1] + dx, o_current->line->y[1] + dy);

  gschem_cairo_set_source_color (w_current,
                                 x_color_lookup_dark (o_current->color));
  gschem_cairo_stroke (w_current, TYPE_SOLID, END_NONE, size, -1, -1);
}
