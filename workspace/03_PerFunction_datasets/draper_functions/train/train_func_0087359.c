calc_indent (PangoContext *context, const GnmStyle *mstyle)
{
	int indent = 0;
	if (gnm_style_is_element_set (mstyle, MSTYLE_INDENT)) {
		int n = gnm_style_get_indent (mstyle);
		if (n) {
			GnmFont *style_font = gnm_style_get_font (mstyle, context);
			indent = PANGO_PIXELS (n * style_font->go.metrics->avg_digit_width);
		}
	}
	return MIN (indent, 65535);
}
