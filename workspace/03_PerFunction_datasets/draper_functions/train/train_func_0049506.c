goo_canvas_create_pattern_from_color_value (const GValue *value)
{
  GdkColor color = { 0, 0, 0, 0, };

  if (g_value_get_string (value))
    gdk_color_parse (g_value_get_string (value), &color);

  return cairo_pattern_create_rgb (color.red / 65535.0,
				   color.green / 65535.0,
				   color.blue / 65535.0);
}
