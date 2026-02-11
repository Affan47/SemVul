gconf_tree_model_get_gconf_name (GConfTreeModel *tree_model, GtkTreeIter *iter)
{
	gchar *ptr;
	Node *node = iter->user_data;

	ptr = node->path + strlen (node->path);

	while (ptr[-1] != '/')
		ptr--;

	return g_strdup (ptr);
}
