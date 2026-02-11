o_pin_draw(GSCHEM_TOPLEVEL *w_current, OBJECT *o_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int x1, y1, x2, y2;
  int size = 0;

  if (o_current->line == NULL) {
    return;
  }


  if (!o_line_visible (w_current, o_current->line, &x1, &y1, &x2, &y2)) {
    return;
  }

  if (toplevel->pin_style == THICK)
    size = o_current->line_width;

  gschem_cairo_line (w_current, END_NONE, size, x1, y1, x2, y2);

  gschem_cairo_set_source_color (w_current,
                                 o_drawing_color (w_current, o_current));
  gschem_cairo_stroke (w_current, TYPE_SOLID, END_NONE, size, -1, -1);


  o_cue_draw_lowlevel(w_current, o_current, o_current->whichend);

#if DEBUG
  printf("drawing pin\n");
#endif

  if (o_current->selected && w_current->draw_grips) {
    o_line_draw_grips (w_current, o_current);
  }
}
