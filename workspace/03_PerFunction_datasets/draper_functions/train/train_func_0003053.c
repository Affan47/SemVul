on_external_open(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkTreeSelection *treesel;
	GtkTreeModel *model;
	GList *list;
	gboolean dir_found;

	treesel = gtk_tree_view_get_selection(GTK_TREE_VIEW(file_view));

	list = gtk_tree_selection_get_selected_rows(treesel, &model);
	dir_found = is_folder_selected(list);

	if (! dir_found || check_single_selection(treesel))
	{
		GList *item;

		for (item = list; item != NULL; item = g_list_next(item))
		{
			GtkTreePath *treepath = item->data;
			gchar *fname = get_tree_path_filename(treepath);

			open_external(fname, dir_found);
			g_free(fname);
		}
	}

	g_list_foreach(list, (GFunc) gtk_tree_path_free, NULL);
	g_list_free(list);
}
