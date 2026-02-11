merge_spec_from_root (xmlNodePtr root, const gchar *provider, xmlDocPtr pdoc)
{

	GSList *paths, *list;

	paths = make_paths (xmlDocGetRootElement (pdoc), "", NULL);
	for (list = paths; list; list = list->next) {
		Path *path = (Path *) list->data;


		xmlNodePtr node = NULL;
		for (node = root->children; node; node = node->next) {
			if (!strcmp ((gchar*) node->name, "path")) {
				xmlChar *pid;
				pid = xmlGetProp (node, BAD_CAST "id");
				if (pid) {
					if (!strcmp ((gchar*) pid, path->path)) {
						xmlFree (pid);
						break;
					}
					xmlFree (pid);
				}
			}

		}
		if (!node) {
			node = xmlNewChild (root, NULL, BAD_CAST "path", NULL);
			xmlSetProp (node, BAD_CAST "id", BAD_CAST path->path);
			xmlSetProp (node, BAD_CAST "node_type", BAD_CAST node_type_to_string (path->node_type));
			if (path->type && *path->type)
				xmlSetProp (node, BAD_CAST "gdatype", BAD_CAST path->type);
		}


		xmlNodePtr pnode;
		if (!prov) {
			pnode = xmlNewChild (node, NULL, BAD_CAST "prov", NULL);
			xmlSetProp (pnode, BAD_CAST "prov_name", BAD_CAST provider);
		}
		else
			pnode = node;
		xmlSetProp (pnode, BAD_CAST "name", BAD_CAST path->name);
		if (path->descr && *path->descr)
			xmlSetProp (pnode, BAD_CAST "descr", BAD_CAST path->descr);

		if (!prov) {

			xmlChar *node_type;
			node_type = xmlGetProp (node, BAD_CAST "node_type");
			g_assert (node_type);
			if (strcmp ((gchar*) node_type,
				    node_type_to_string (path->node_type)))
				xmlSetProp (pnode, BAD_CAST "node_type",
					    BAD_CAST node_type_to_string (path->node_type));
			xmlFree (node_type);


			node_type = xmlGetProp (node, BAD_CAST "gdatype");
			if ((node_type && path->type &&
			     strcmp ((gchar*) node_type, path->type)) ||
			    (!node_type && path->type) ||
			    (node_type && *node_type && !path->type))
				xmlSetProp (pnode, BAD_CAST "gdatype", BAD_CAST path->type);
			if (node_type)
				xmlFree (node_type);
		}
	}


	g_slist_foreach (paths, (GFunc) path_free, NULL);
	g_slist_free (paths);
}
