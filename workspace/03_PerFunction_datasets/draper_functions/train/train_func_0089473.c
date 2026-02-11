reparent_node (FileBrowserNode *node,
	       gboolean         reparent)
{
	if (!node->file)
		return;

	if (reparent)
	{
		GFile *parent;
		gchar *base;

		parent = node->parent->file;
		base = g_file_get_basename (node->file);
		g_object_unref (node->file);

		node->file = g_file_get_child (parent, base);
		g_free (base);
	}

	if (NODE_IS_DIR (node))
	{
		FileBrowserNodeDir *dir;
		GSList *child;

		dir = FILE_BROWSER_NODE_DIR (node);

		for (child = dir->children; child; child = child->next)
		{
			reparent_node ((FileBrowserNode *)child->data, TRUE);
		}
	}
}
