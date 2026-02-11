update_file_list (gpointer user_data)
{
	DialogData *data = user_data;
	LoaderData *loader_data;
	GList      *items;
	GList      *file_data_list;

	if (data->update_selectection_event != 0) {
		g_source_remove (data->update_selectection_event);
		data->update_selectection_event = 0;
	}

	cancel_file_list_loading (data);

	loader_data = g_new0 (LoaderData, 1);
	loader_data->data = dialog_data_ref (data);

	items = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_browser_get_file_list_view (data->browser)));
	file_data_list = gth_file_list_get_files (GTH_FILE_LIST (gth_browser_get_file_list (data->browser)), items);
	loader_data->files = gth_file_data_list_to_file_list (file_data_list);

	data->loader = gth_load_file_data_task_new (loader_data->files, "*");
	g_signal_connect (data->loader,
			  "completed",
			  G_CALLBACK (loader_completed_cb),
			  loader_data);
	gth_browser_exec_task (data->browser, data->loader, FALSE);

	_g_object_list_unref (file_data_list);
	_gtk_tree_path_list_free (items);

	return FALSE;
}
