go_color_to_pango (GOColor color, gboolean is_fore)
{
	guint16 r, g, b;
	r  = GO_COLOR_UINT_R (color);
	r |= (r << 8);
	g  = GO_COLOR_UINT_G (color);
	g |= (g << 8);
	b  = GO_COLOR_UINT_B (color);
	b |= (b << 8);

	if (is_fore)
		return pango_attr_foreground_new (r, g, b);
	else
		return pango_attr_background_new (r, g, b);
}
