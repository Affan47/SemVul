odf_custom_shape_equation (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	gchar const *name = NULL, *meaning = NULL;
	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]),
					OO_NS_DRAW, "name"))
			name = CXML2C (attrs[1]);
		else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]),
					     OO_NS_DRAW, "formula"))
			meaning = CXML2C (attrs[1]);
	if (name && meaning) {
		if (state->chart.cs_variables == NULL)
			state->chart.cs_variables = g_hash_table_new_full
				(g_str_hash, g_str_equal,
				 (GDestroyNotify) g_free, (GDestroyNotify) g_free);
		g_hash_table_insert (state->chart.cs_variables,
				     g_strdup_printf ("?%s", name), g_strdup (meaning));
	}
}
