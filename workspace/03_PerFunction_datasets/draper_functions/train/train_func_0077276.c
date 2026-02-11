cb_append_row(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer user)
{
	GSList		**sel = user;
	GtkTreeIter	*di;

	if((di = g_malloc(sizeof *di)) != NULL)
	{
		*di = *iter;
		*sel = g_slist_prepend(*sel, di);
	}
}
