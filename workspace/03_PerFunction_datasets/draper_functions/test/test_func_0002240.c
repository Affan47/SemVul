oo_style_prop_col_row (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	char const * const size_tag = (state->cur_style.type == OO_STYLE_COL)
		? "column-width" :  "row-height";
	char const * const use_optimal = (state->cur_style.type == OO_STYLE_COL)
		? "use-optimal-column-width" : "use-optimal-row-height";
	gnm_float pts;
	gboolean auto_size;

	g_return_if_fail (state->cur_style.col_rows != NULL);

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (NULL != oo_attr_distance (xin, attrs, OO_NS_STYLE, size_tag, &pts))
			state->cur_style.col_rows->size_pts = pts;
		else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_FO, "break-before"))
			state->cur_style.col_rows->break_before =
				oo_page_break_type (xin, attrs[1]);
		else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_FO, "break-after"))
			state->cur_style.col_rows->break_after =
				oo_page_break_type (xin, attrs[1]);
		else if (oo_attr_bool (xin, attrs, OO_NS_STYLE, use_optimal, &auto_size))
			state->cur_style.col_rows->manual = !auto_size;
}
