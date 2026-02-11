gnm_style_set_pattern_color (GnmStyle *style, GnmColor *col)
{
	g_return_if_fail (style != NULL);
	g_return_if_fail (col != NULL);

	elem_changed (style, MSTYLE_COLOR_PATTERN);
	if (elem_is_set (style, MSTYLE_COLOR_PATTERN))
		style_color_unref (style->color.pattern);
	else
		elem_set (style, MSTYLE_COLOR_PATTERN);
	style->color.pattern = col;
	gnm_style_clear_pango (style);
}
