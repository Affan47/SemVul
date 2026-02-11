oo_date_style (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	char const *name = NULL;
	int magic = GO_FORMAT_MAGIC_NONE;
	gboolean format_source_is_language = FALSE;
	gboolean truncate_hour_on_overflow = TRUE;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_STYLE, "name"))
			name = CXML2C (attrs[1]);
		else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_STYLE, "family") &&
			 !attr_eq (attrs[1], "data-style"))
			return;
		else if (oo_attr_int (xin, attrs, OO_GNUM_NS_EXT,
				      "format-magic", &magic))
			;
		else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_NUMBER, "format-source"))
			format_source_is_language = attr_eq (attrs[1], "language");
		else if (oo_attr_bool (xin, attrs, OO_NS_NUMBER,
				       "truncate-on-overflow", &truncate_hour_on_overflow));

	g_return_if_fail (state->cur_format.accum == NULL);


	state->cur_format.magic = format_source_is_language ? magic : GO_FORMAT_MAGIC_NONE;
	state->cur_format.accum = (state->cur_format.magic == GO_FORMAT_MAGIC_NONE) ?  g_string_new (NULL) : NULL;
	state->cur_format.name = g_strdup (name);
	state->cur_format.percentage = FALSE;
	state->cur_format.truncate_hour_on_overflow = truncate_hour_on_overflow;
	state->cur_format.elapsed_set = 0;
	state->cur_format.pos_seconds = 0;
	state->cur_format.pos_minutes = 0;
}
