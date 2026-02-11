gedit_file_browser_store_delete_all (GeditFileBrowserStore *model,
				     GList                 *rows,
				     gboolean               trash)
{
	FileBrowserNode *node;
	AsyncData *data;
	GList *files = NULL;
	GList *row;
	GtkTreeIter iter;
	GtkTreePath *prev = NULL;
	GtkTreePath *path;

	g_return_val_if_fail (GEDIT_IS_FILE_BROWSER_STORE (model), GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE);

	if (rows == NULL)
		return GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE;


	rows = g_list_sort (g_list_copy (rows), (GCompareFunc)gtk_tree_path_compare);

	for (row = rows; row; row = row->next)
	{
		path = (GtkTreePath *)(row->data);

		if (!gtk_tree_model_get_iter (GTK_TREE_MODEL (model), &iter, path))
			continue;


		if (prev != NULL && gtk_tree_path_is_descendant (path, prev))
			continue;

		prev = path;
		node = (FileBrowserNode *)(iter.user_data);
		files = g_list_prepend (files, g_object_ref (node->file));
	}

	data = g_slice_new (AsyncData);

	data->model = model;
	data->cancellable = g_cancellable_new ();
	data->files = files;
	data->trash = trash;
	data->iter = files;
	data->removed = FALSE;

	model->priv->async_handles = g_slist_prepend (model->priv->async_handles, data);

	delete_files (data);
	g_list_free (rows);

	return GEDIT_FILE_BROWSER_STORE_RESULT_OK;
}
