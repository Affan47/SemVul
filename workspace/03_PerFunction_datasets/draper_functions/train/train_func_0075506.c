vflist_selection_count(ViewFile *vf, gint64 *bytes)
{
	GtkTreeModel *store;
	GtkTreeSelection *selection;
	GList *slist;
	guint count;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(vf->listview));
	slist = gtk_tree_selection_get_selected_rows(selection, &store);

	if (bytes)
		{
		gint64 b = 0;
		GList *work;

		work = slist;
		while (work)
			{
			GtkTreePath *tpath = work->data;
			GtkTreeIter iter;
			FileData *fd;

			gtk_tree_model_get_iter(store, &iter, tpath);
			gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &fd, -1);
			b += fd->size;

			work = work->next;
			}

		*bytes = b;
		}

	count = g_list_length(slist);
	g_list_foreach(slist, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(slist);

	return count;
}
