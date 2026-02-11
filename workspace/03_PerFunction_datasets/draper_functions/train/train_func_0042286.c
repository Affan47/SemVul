odf_page_layout (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	char const *name = NULL;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_STYLE, "name"))
			name = CXML2C (attrs[1]);

	if (name == NULL) {
		oo_warning (xin, _("Missing page layout identifier"));
		name = "Missing page layout identifier";
	}
	state->print.cur_pi = print_information_new (TRUE);
	g_hash_table_insert (state->styles.page_layouts, g_strdup (name),
			     state->print.cur_pi);
}
