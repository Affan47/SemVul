xlsx_font_color (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;


	GnmColor *color = elem_color (xin, attrs, FALSE);
	if (NULL != color)
		gnm_style_set_font_color (state->style_accum, color);
}
