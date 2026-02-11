dest_view_bookmark(Dest_Data *dd, GtkTreeView *view)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *path;

	if (!dd->right_click_path) return;

	model = gtk_tree_view_get_model(view);
	gtk_tree_model_get_iter(model, &iter, dd->right_click_path);
	gtk_tree_model_get(model, &iter, 1, &path, -1);

	bookmark_list_add(dd->bookmark_list, filename_from_path(path), path);
	g_free(path);
}
