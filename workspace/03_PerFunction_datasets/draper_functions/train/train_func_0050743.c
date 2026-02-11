oo_date_month (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	gboolean as_text = FALSE;
	gboolean is_short = TRUE;

	if (state->cur_format.accum == NULL)
		return;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_NUMBER, "style"))
			is_short = attr_eq (attrs[1], "short");
		else if (oo_attr_bool (xin, attrs, OO_NS_NUMBER, "textual", &as_text))
			;
	g_string_append (state->cur_format.accum, as_text
			 ? (is_short ? "mmm" : "mmmm")
			 : (is_short ? "m" : "mm"));
}
