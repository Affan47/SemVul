xl_xml_named_range (GsfXMLIn *xin, xmlChar const **attrs)
{
	ExcelXMLReadState *state = (ExcelXMLReadState *)xin->user_state;
	char const *name = NULL;
	char const *expr_str = NULL;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, attrs[0], XL_NS_SS, "Name"))
			name = attrs[1];
		else if (gsf_xml_in_namecmp (xin, attrs[0], XL_NS_SS, "RefersTo"))
			expr_str = attrs[1];

	if (NULL != name && NULL != expr_str) {
		GnmParsePos pp;
		GnmExprTop const *texpr = xl_xml_parse_expr (xin, expr_str,
			parse_pos_init (&pp, state->wb, NULL, 0, 0));
		g_warning ("%s = %s", name, expr_str);
		if (NULL != texpr)
			expr_name_add (&pp, name, texpr, NULL, TRUE, NULL);
	}
}
