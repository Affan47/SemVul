on_config_file_clicked(G_GNUC_UNUSED GtkWidget *widget, gpointer user_data)
{
	const gchar *file_name = user_data;
	GeanyFiletype *ft = NULL;

	if (strstr(file_name, G_DIR_SEPARATOR_S "filetypes."))
		ft = filetypes_index(GEANY_FILETYPES_CONF);

	if (g_file_test(file_name, G_FILE_TEST_EXISTS))
		document_open_file(file_name, FALSE, ft, NULL);
	else
	{
		gchar *utf8_filename = utils_get_utf8_from_locale(file_name);
		gchar *base_name = g_path_get_basename(file_name);
		gchar *global_file = g_build_filename(geany->app->datadir, base_name, NULL);
		gchar *global_content = NULL;


		if (g_file_test(global_file, G_FILE_TEST_EXISTS))
			g_file_get_contents(global_file, &global_content, NULL, NULL);

		document_new_file(utf8_filename, ft, global_content);

		g_free(utf8_filename);
		g_free(base_name);
		g_free(global_file);
		g_free(global_content);
	}
}
