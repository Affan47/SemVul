refresh_row (gpointer data,
             gpointer user_data)
{
	NautilusFile *file;
	NautilusListModel *model;
	GList *iters, *l;
	GtkTreePath *path;

	model = user_data;
	file = data;

	iters = nautilus_list_model_get_all_iters_for_file (model, file);
	for (l = iters; l != NULL; l = l->next) {
		path = gtk_tree_model_get_path (GTK_TREE_MODEL (model), l->data);
		gtk_tree_model_row_changed (GTK_TREE_MODEL (model), path, l->data);

		gtk_tree_path_free (path);
	}

	g_list_free_full (iters, g_free);
}
