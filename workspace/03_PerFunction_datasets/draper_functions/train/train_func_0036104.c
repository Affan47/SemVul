extract_gog_object_style (XLExportBase *ewb, GogObject *obj)
{
	GSList *ptr = obj->children;

	if (GOG_IS_STYLED_OBJECT (obj)) {
		GOStyle const *style = GOG_STYLED_OBJECT (obj)->style;
		if (style->interesting_fields & (GO_STYLE_OUTLINE | GO_STYLE_LINE))
			put_color_go_color (ewb, style->line.color);
		if (style->interesting_fields & GO_STYLE_FILL)
			switch (style->fill.type) {
			default :
			case GO_STYLE_FILL_NONE :
			case GO_STYLE_FILL_IMAGE :
				break;
			case GO_STYLE_FILL_PATTERN :
				put_color_go_color (ewb, style->fill.pattern.fore);
				put_color_go_color (ewb, style->fill.pattern.back);
				break;
			case GO_STYLE_FILL_GRADIENT :
				put_color_go_color (ewb, style->fill.pattern.fore);
			}
		if (style->interesting_fields & GO_STYLE_MARKER) {
			put_color_go_color (ewb, go_marker_get_outline_color (style->marker.mark));
			put_color_go_color (ewb, go_marker_get_fill_color (style->marker.mark));
		}

		if (style->interesting_fields & GO_STYLE_FONT)
			excel_font_from_go_font (ewb, style->font.font);
	}
	if (GOG_IS_AXIS (obj)) {
		char *fmt_str;
		g_object_get (G_OBJECT (obj), "assigned-format-string-XL", &fmt_str, NULL);
		if (fmt_str != NULL) {
			GOFormat *fmt = go_format_new_from_XL (fmt_str);
			if (!go_format_is_general (fmt))
				two_way_table_put (ewb->formats.two_way_table,
						   (gpointer)fmt, TRUE,
						   (AfterPutFunc) after_put_format,
						   "Found unique format %d - 0x%x\n");
			else
				go_format_unref (fmt);
		}
		g_free (fmt_str);
	}

	for ( ; ptr != NULL ; ptr = ptr->next)
		extract_gog_object_style (ewb, ptr->data);
}
