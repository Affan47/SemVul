for_each_child__catalog_list_ready_cb (GthCatalog *catalog,
				       GList      *files,
				       GError     *error,
				       gpointer    user_data)
{
	ForEachChildData *data = user_data;
	GList            *scan;

	for (scan = files; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;

		if (g_file_info_get_is_hidden (file_data->info))
			continue;

		data->for_each_file_func (file_data->file,
					  file_data->info,
					  data->user_data);
	}

	for_each_child__continue (data);
}
