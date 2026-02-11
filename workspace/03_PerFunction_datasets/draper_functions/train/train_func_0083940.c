gth_browser_activate_action_file_open (GtkAction  *action,
				       GthBrowser *browser)
{
	GList *items;
	GList *file_list;

	items = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_browser_get_file_list_view (browser)));
	file_list = gth_file_list_get_files (GTH_FILE_LIST (gth_browser_get_file_list (browser)), items);

	if (file_list != NULL)
		gth_browser_load_file (browser, (GthFileData *) file_list->data, TRUE);

	_g_object_list_unref (file_list);
	_gtk_tree_path_list_free (items);
}
