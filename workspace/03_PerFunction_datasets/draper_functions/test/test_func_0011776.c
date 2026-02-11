make_paths (xmlNodePtr node, const gchar *parent_path, GSList *exist_list)
{
	xmlChar *id;
	GSList *retlist = exist_list;
	id = xmlGetProp (node, BAD_CAST "id");
	if (id) {
		Path *path;
		gchar *pstr = g_strdup_printf ("%s/%s", parent_path, id);

		path = g_new0 (Path, 1);
		path->path = pstr;
		retlist = g_slist_append (retlist, path);

		if (!strcmp ((gchar*) node->name, "parameters"))
			path->node_type = GDA_SERVER_OPERATION_NODE_PARAMLIST;
		else if (!strcmp ((gchar*) node->name, "parameter"))
			path->node_type = GDA_SERVER_OPERATION_NODE_PARAM;
		else if (!strcmp ((gchar*) node->name, "sequence"))
			path->node_type = GDA_SERVER_OPERATION_NODE_SEQUENCE;
		else if (!strcmp ((gchar*) node->name, "gda_array"))
			path->node_type = GDA_SERVER_OPERATION_NODE_DATA_MODEL;
		else if (!strcmp ((gchar*) node->name, "gda_array_field")) {
			path->node_type = GDA_SERVER_OPERATION_NODE_DATA_MODEL_COLUMN;
			g_free (path->path);
			pstr = g_strdup_printf ("%s/@%s", parent_path, id);
			path->path = pstr;
		}
		else
			path->node_type = GDA_SERVER_OPERATION_NODE_UNKNOWN;

		xmlChar *prop;
		prop = xmlGetProp (node, BAD_CAST "name");
		if (prop) {
			path->name = g_strdup ((gchar*) prop);
			xmlFree (prop);
		}
		prop = xmlGetProp (node, BAD_CAST "descr");
		if (prop) {
			path->descr = g_strdup ((gchar*) prop);
			xmlFree (prop);
		}
		prop = xmlGetProp (node, BAD_CAST "gdatype");
		if (prop) {
			path->type = g_strdup ((gchar*) prop);
			xmlFree (prop);
		}


		xmlNodePtr child;
		for (child = node->children; child; child = child->next)
			retlist = make_paths (child, pstr, retlist);

		xmlFree (id);
	}
	else {

		xmlNodePtr child;
		for (child = node->children; child; child = child->next)
			retlist = make_paths (child, parent_path, retlist);
	}

	return retlist;
}
