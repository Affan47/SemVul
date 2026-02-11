xmlparse_estategroupupdate(guint32 connectid, xmlDocPtr doc, xmlNodePtr cur)  {

	xmlChar *tmp;
	gint32 groupid = -1;
	(void)connectid;
	(void)doc;

	tmp = xmlGetProp(cur, (xmlChar*)"groupid");
	if(tmp)  {
		groupid = atoi((gchar*)tmp);
		g_free(tmp);
	}

	if(groupid < 0)  return;

	if(game->group[groupid].name)  g_free(game->group[groupid].name);

	game->group[groupid].name = (gchar*)xmlGetProp(cur, (xmlChar*)"name");
}
