gnm_style_get_font_name (GnmStyle const *style)
{
	g_return_val_if_fail (style != NULL, NULL);
	g_return_val_if_fail (elem_is_set (style, MSTYLE_FONT_NAME), NULL);

	return style->font_detail.name->str;
}
