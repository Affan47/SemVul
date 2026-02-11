aurora_draw_separator (cairo_t * cr,
		       const AuroraColors * colors,
		       const WidgetParameters * widget,
		       const SeparatorParameters * separator,
		       int x, int y, int width, int height)
{

  AuroraRGB dark = colors->bg[widget->state_type];
  AuroraRGB light;

  aurora_shade (&dark, &light, 1.15);
  aurora_shade (&dark, &dark, 0.68);


  if (separator->horizontal) {
    cairo_translate (cr, x + 0.5, y + 0.5);

    cairo_move_to (cr, 0.0, 0.0);
    cairo_line_to (cr, width, 0.0);
    cairo_set_source_rgba (cr, dark.r, dark.g, dark.b, 0.6);
    cairo_stroke (cr);

    cairo_move_to (cr, 0.0, 1.0);
    cairo_line_to (cr, width, 1.0);
    cairo_set_source_rgba (cr, light.r, light.g, light.b, 0.6);
    cairo_stroke (cr);
  }
  else {
    cairo_translate (cr, x + 0.5, y + 0.5);

    cairo_move_to (cr, 0.0, 0.0);
    cairo_line_to (cr, 0.0, height);
    cairo_set_source_rgba (cr, dark.r, dark.g, dark.b, 0.6);
    cairo_stroke (cr);

    cairo_move_to (cr, 1.0, 0.0);
    cairo_line_to (cr, 1.0, height);
    cairo_set_source_rgba (cr, light.r, light.g, light.b, 0.6);
    cairo_stroke (cr);
  }
}
