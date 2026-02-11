catalog_buffer_ready_cb (void     **buffer,
			 gsize      count,
			 GError    *error,
			 gpointer   user_data)
{
	RemoveFromCatalogData *data = user_data;
	GList                 *scan;
	void                  *catalog_buffer;
	gsize                  catalog_size;

	if (error != NULL) {
		remove_from_catalog_end (error, data);
		return;
	}

	data->catalog = gth_hook_invoke_get ("gth-catalog-load-from-data", *buffer);
	if (data->catalog == NULL) {
		error = g_error_new_literal (G_IO_ERROR, G_IO_ERROR_FAILED, _("Invalid file format"));
		remove_from_catalog_end (error, data);
		return;
	}

	gth_catalog_load_from_data (data->catalog, *buffer, count, &error);
	if (error != NULL) {
		remove_from_catalog_end (error, data);
		return;
	}

	for (scan = data->file_data_list; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;
		gth_catalog_remove_file (data->catalog, file_data->file);
	}

	catalog_buffer = gth_catalog_to_data (data->catalog, &catalog_size);
	if (error != NULL) {
		remove_from_catalog_end (error, data);
		return;
	}

	_g_file_write_async (data->gio_file,
			     catalog_buffer,
			     catalog_size,
			     TRUE,
			     G_PRIORITY_DEFAULT,
			     NULL,
			     remove_files__catalog_save_done_cb,
			     data);
}
