_update_statusbar_list_info (GthBrowser *browser)
{
	GList   *file_list;
	int      n_total;
	goffset  size_total;
	GList   *scan;
	int      n_selected;
	goffset  size_selected;
	GList   *selected;
	char    *size_total_formatted;
	char    *size_selected_formatted;
	char    *text_total;
	char    *text_selected;
	GString *text;


	file_list = gth_file_store_get_visibles (gth_browser_get_file_store (browser));
	n_total = 0;
	size_total = 0;
	for (scan = file_list; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;

		n_total++;
		size_total += g_file_info_get_size (file_data->info);
	}
	_g_object_list_unref (file_list);


	selected = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_browser_get_file_list_view (browser)));
	file_list = gth_file_list_get_files (GTH_FILE_LIST (gth_browser_get_file_list (browser)), selected);

	n_selected = 0;
	size_selected = 0;
	for (scan = file_list; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;

		n_selected++;
		size_selected += g_file_info_get_size (file_data->info);
	}
	_g_object_list_unref (file_list);
	_gtk_tree_path_list_free (selected);


	size_total_formatted = g_format_size (size_total);
	size_selected_formatted = g_format_size (size_selected);
	text_total = g_strdup_printf (g_dngettext (NULL, "%d file (%s)", "%d files (%s)", n_total), n_total, size_total_formatted);
	text_selected = g_strdup_printf (g_dngettext (NULL, "%d file selected (%s)", "%d files selected (%s)", n_selected), n_selected, size_selected_formatted);

	text = g_string_new (text_total);
	if (n_selected > 0) {
		g_string_append (text, STATUSBAR_SEPARATOR);
		g_string_append (text, text_selected);
	}
	if (browser->priv->location_free_space != NULL) {
		g_string_append (text, STATUSBAR_SEPARATOR);
		g_string_append (text, browser->priv->location_free_space);
	}
	gth_statusbar_set_list_info (GTH_STATUSBAR (browser->priv->statusbar), text->str);

	g_string_free (text, TRUE);
	g_free (text_selected);
	g_free (text_total);
	g_free (size_selected_formatted);
	g_free (size_total_formatted);
}
