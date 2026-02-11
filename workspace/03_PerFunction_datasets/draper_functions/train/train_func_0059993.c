od_meta_user_defined (GsfXMLIn *xin,  xmlChar const **attrs)
{
	GsfOOMetaIn *mi = (GsfOOMetaIn *)xin->user_state;
	mi->typ = G_TYPE_NONE;
	mi->name = NULL;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2) {
		if (!strcmp (CXML2C (attrs[0]), "meta:name"))
			mi->name = g_strdup (CXML2C (attrs[1]));
		else if (!strcmp (CXML2C (attrs[0]), "meta:value-type") ||
			 !strcmp (CXML2C (attrs[0]), "meta:type")) {


			if (!strcmp (CXML2C (attrs[1]), "boolean")) {
				mi->typ = G_TYPE_BOOLEAN;
			} else if (!strcmp (CXML2C (attrs[1]), "float")) {
				mi->typ = G_TYPE_DOUBLE;
			} else if (!strcmp (CXML2C (attrs[1]), "string")) {
				mi->typ = G_TYPE_STRING;
			} else if (!strcmp (CXML2C (attrs[1]), "date") ||
				   !strcmp (CXML2C (attrs[1]), "data")) {


				mi->typ = GSF_TIMESTAMP_TYPE;
			} else if (!strcmp (CXML2C (attrs[1]), "time")) {
				mi->typ = G_TYPE_STRING;

			} else {

			}
		}
	}
	if (mi->name == NULL)
		mi->name = g_strdup ("");
}
