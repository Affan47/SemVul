dae_xml_next_child_by_tagname(xmlNodePtr parent, xmlNodePtr *node,
	gchar *nodename)
{
	xmlNodePtr tmpnode;
	gchar *name;

	do {
		tmpnode = dae_xml_next_child(NULL, parent, node, NULL, &name);
		if(tmpnode == NULL)
			return NULL;
		if(strcmp(name, nodename) == 0) {
			g_free(name);
			return tmpnode;
		}
		g_free(name);
	} while(1);
}
