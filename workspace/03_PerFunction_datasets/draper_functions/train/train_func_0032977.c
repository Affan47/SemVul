xml_sax_page_break (GsfXMLIn *xin, xmlChar const **attrs)
{
	XMLSaxParseState *state = (XMLSaxParseState *)xin->user_state;
	GnmPageBreakType  type = GNM_PAGE_BREAK_NONE;
	int pos = -1;

	if (NULL == state->page_breaks)
		return;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gnm_xml_attr_int (attrs, "pos", &pos)) ;
		else if (!strcmp (CXML2C (attrs[0]), "type"))
			type = gnm_page_break_type_from_str (CXML2C (attrs[1]));


	gnm_page_breaks_append_break (state->page_breaks, pos, type);
}
