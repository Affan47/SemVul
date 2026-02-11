file_model_row_expanded (GtkTreeView* tree_view, GtkTreeIter* iter,
					    GtkTreePath* path, gpointer user_data)
{
	GtkTreeModel* sort_model = gtk_tree_view_get_model(tree_view);
	FileModel* model = FILE_MODEL(user_data);
	GFile* dir;
	GtkTreeIter real_iter;
	GCancellable* cancel = g_cancellable_new ();
	GtkTreePath* real_path;

	DEBUG_PRINT ("%s", "row_expanded");

	gtk_tree_model_sort_convert_iter_to_child_iter(GTK_TREE_MODEL_SORT(sort_model),
												   &real_iter, iter);

	gtk_tree_model_get(GTK_TREE_MODEL(model), &real_iter,
					   COLUMN_FILE, &dir, -1);

	FileModelAsyncData* data = g_new0 (FileModelAsyncData, 1);
	data->model = model;
	real_path = gtk_tree_model_get_path (GTK_TREE_MODEL (model),
									&real_iter);
	data->reference = gtk_tree_row_reference_new (GTK_TREE_MODEL (model),
												  real_path);
	gtk_tree_path_free (real_path);

	g_object_set_data (G_OBJECT(dir), "_cancel", cancel);

	g_file_enumerate_children_async (dir,
									 "standard::*",
									 G_FILE_QUERY_INFO_NONE,
									 G_PRIORITY_LOW,
									 cancel,
									 on_row_expanded_async,
									 data);
	g_object_unref (dir);
}
