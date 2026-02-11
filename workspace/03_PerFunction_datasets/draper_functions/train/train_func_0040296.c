xml_sax_style_border (GsfXMLIn *xin, xmlChar const **attrs)
{
	XMLSaxParseState *state = (XMLSaxParseState *)xin->user_state;

	int pattern = -1;
	GnmColor *colour = NULL;

	xml_sax_must_have_style (state);


	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2) {
		if (xml_sax_attr_color (attrs, "Color", &colour)) ;
		else if (gnm_xml_attr_int (attrs, "Style", &pattern)) ;
		else
			unknown_attr (xin, attrs);
	}

	if (pattern >= GNM_STYLE_BORDER_NONE) {
		GnmStyleElement const type = xin->node->user_data.v_int;
		GnmStyleBorderLocation const loc =
			GNM_STYLE_BORDER_TOP + (int)(type - MSTYLE_BORDER_TOP);
		GnmBorder *border;


		if (!colour)
			colour = gnm_color_new_go (GO_COLOR_BLACK);

		border = gnm_style_border_fetch
			((GnmStyleBorderType)pattern, colour,
			 gnm_style_border_get_orientation (loc));
		gnm_style_set_border (state->style, type, border);
	}
}
