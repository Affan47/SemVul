brasero_data_project_node_to_path (BraseroDataProject *self,
				   BraseroFileNode *node)
{
	guint len;
	GSList *list;
	GSList *iter;
	gchar path [MAXPATHLEN] = {0, };

	if (!node || G_NODE_IS_ROOT (node))
		return g_strdup (G_DIR_SEPARATOR_S);


	list = NULL;
	while (node->parent) {
		list = g_slist_prepend (list, node);
		node = node->parent;
	}

	len = 0;
	for (iter = list; iter; iter = iter->next) {
		gchar *name;
		guint name_len;

		node = iter->data;

		*(path + len) = G_DIR_SEPARATOR;
		len ++;

		if (len > MAXPATHLEN)
			return NULL;


		name = BRASERO_FILE_NODE_NAME (node);

		name_len = strlen (name);
		if (len + name_len > MAXPATHLEN)
			return NULL;

		memcpy (path + len, name, name_len);
		len += name_len;
	}
	g_slist_free (list);

	return g_strdup (path);
}
