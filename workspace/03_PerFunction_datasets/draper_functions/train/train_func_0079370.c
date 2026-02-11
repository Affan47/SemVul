duplicates_list_view_selection_changed_cb (GthFileView *fileview,
					   gpointer     user_data)
{

	GthFindDuplicates *self = user_data;
	GList             *file_data_list;
	GHashTable        *selected_files;
	GtkTreeModel      *files_treemodel;
	GtkTreeIter        iter;
	GList             *scan;

	selected_files = g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
	file_data_list = get_duplicates_file_data_list (self);
	for (scan = file_data_list; scan; scan = scan->next) {
		GthFileData    *selected_file_data = (GthFileData *) scan->data;
		const char     *checksum;
		DuplicatedData *d_data;
		GList          *scan_duplicated;

		checksum = g_file_info_get_attribute_string (selected_file_data->info, "find-duplicates::checksum");
		d_data = g_hash_table_lookup (self->priv->duplicated, checksum);

		g_return_if_fail (d_data != NULL);

		for (scan_duplicated = d_data->files; scan_duplicated; scan_duplicated = scan_duplicated->next) {
			GthFileData *file_data = scan_duplicated->data;
			g_hash_table_insert (selected_files, g_object_ref (file_data->file), GINT_TO_POINTER (1));
		}
	}

	files_treemodel = GTK_TREE_MODEL (GET_WIDGET ("files_liststore"));
	if (gtk_tree_model_get_iter_first (files_treemodel, &iter)) {
		do {
			GthFileData *file_data;

			gtk_tree_model_get (files_treemodel, &iter,
					    FILE_LIST_COLUMN_FILE, &file_data,
					    -1);
			gtk_list_store_set (GTK_LIST_STORE (files_treemodel), &iter,
					    FILE_LIST_COLUMN_VISIBLE, (g_hash_table_lookup (selected_files, file_data->file) != NULL),
					    -1);

			g_object_unref (file_data);
		}
		while (gtk_tree_model_iter_next (files_treemodel, &iter));
	}

	update_file_list_sensitivity (self);
	update_file_list_selection_info (self);

	_g_object_list_unref (file_data_list);
	g_hash_table_unref (selected_files);
}
