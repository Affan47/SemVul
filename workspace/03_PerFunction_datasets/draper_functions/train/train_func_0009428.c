xlsx_pattern_fg_bg (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	gboolean solid_pattern = gnm_style_is_element_set (state->style_accum, MSTYLE_PATTERN)
		&& (1 == gnm_style_get_pattern (state->style_accum));


	gboolean const invert = state->style_accum_partial
		&& solid_pattern;


	GnmColor *color = elem_color (xin, attrs, !solid_pattern);
	if (NULL == color)
		return;

	if (xin->node->user_data.v_int ^ invert)
		gnm_style_set_back_color (state->style_accum, color);
	else
		gnm_style_set_pattern_color (state->style_accum, color);
}
