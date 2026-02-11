gt_tree_view_find_index(GtkTreeView *tree, GtkTreeViewColumn *column)
{
	int index;
	GList *cols;
	GList *iter;

	if (!tree) return -1;
	cols = gtk_tree_view_get_columns(GTK_TREE_VIEW(tree));
	if (!cols) return -1;

	iter = cols;
	index = 0;
	if (HIDDEN_COL)
		iter = g_list_next(iter);

	while (iter)
	{
		if (iter->data == (gpointer)column)
			break;
		iter = g_list_next(iter);
		index++;
	}

	g_list_free(cols);

	if (!iter)
		index = -1;

	return index;
}
