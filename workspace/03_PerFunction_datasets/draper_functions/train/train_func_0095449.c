parse_level_background(Level *l, xmlNodePtr cur) {
	xmlChar *x;

	x = xmlGetProp(cur, (const xmlChar *)"gfxid");
	if(x != NULL)
		l->background = level_get_svgseries_gfxid(l, atoi((char *)x));
}
