search_files_filter_command_finished (SearchFilterFileCommand* cmd,
                                      guint return_code,
                                      SearchFiles* sf)
{
	GFile* file;
	GtkTreeIter iter;
	gchar* display_name = NULL;

	if (return_code)
		return;

	g_object_get (cmd, "file", &file, NULL);

	if (sf->priv->project_file)
	{
		display_name = g_file_get_relative_path (sf->priv->project_file,
		                                         G_FILE (file));
	}
	if (!display_name)
		display_name = g_file_get_path (G_FILE(file));

	gtk_list_store_append(GTK_LIST_STORE (sf->priv->files_model),
	                      &iter);
	gtk_list_store_set (GTK_LIST_STORE (sf->priv->files_model), &iter,
	                    COLUMN_SELECTED, TRUE,
	                    COLUMN_FILENAME, display_name,
	                    COLUMN_FILE, file,
	                    COLUMN_COUNT, 0,
	                    COLUMN_SPINNER, FALSE,
	                    COLUMN_PULSE, FALSE, -1);

	g_object_unref (file);
	g_free (display_name);
}
