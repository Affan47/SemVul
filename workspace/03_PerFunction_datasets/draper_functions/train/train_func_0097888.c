process_rename_data_list (gpointer user_data)
{
	BrowserData *data = user_data;
	GList       *scan;

	g_source_remove (data->update_renamed_files_id);
	data->update_renamed_files_id = 0;

	for (scan = data->rename_data_list; scan; scan = scan->next) {
		RenameData *rename_data = scan->data;
		GthCatalog *catalog;
		GList      *scan_files;
		GList      *scan_new_files;
		GFile      *gio_file;
		char       *catalog_data;
		gsize       catalog_data_size;
		GError     *error = NULL;

		catalog = gth_catalog_load_from_file (rename_data->location);

		for (scan_files = rename_data->files, scan_new_files = rename_data->new_files;
		     scan_files && scan_new_files;
		     scan_files = scan_files->next, scan_new_files = scan_new_files->next)
		{
			GFile *file = scan_files->data;
			GFile *new_file = scan_new_files->data;
			int    pos;

			pos = gth_catalog_remove_file (catalog, file);
			gth_catalog_insert_file (catalog, new_file, pos);
		}

		gio_file = gth_catalog_file_to_gio_file (rename_data->location);
		catalog_data = gth_catalog_to_data (catalog, &catalog_data_size);
		if (! _g_file_write (gio_file,
				     FALSE,
				     G_FILE_CREATE_NONE,
				     catalog_data,
				     catalog_data_size,
				     NULL,
				     &error))
		{
			g_warning ("%s", error->message);
			g_clear_error (&error);
		}

		g_free (catalog_data);
		g_object_unref (gio_file);
		g_object_unref (catalog);
	}

	rename_data_list_free (data);

	return FALSE;
}
