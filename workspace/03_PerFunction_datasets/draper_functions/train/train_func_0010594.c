file_open_cb (GtkAction *action,
	      GSRWindow *window)
{
	GtkWidget *file_chooser;
	gchar *directory;
	gchar *locale_directory = NULL;
	gint response;

	g_return_if_fail (GSR_IS_WINDOW (window));

	file_chooser = gtk_file_chooser_dialog_new (_("Open a File"),
						    GTK_WINDOW (window),
						    GTK_FILE_CHOOSER_ACTION_OPEN,
						    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						    GTK_STOCK_OPEN, GTK_RESPONSE_OK,
						    NULL);

	directory = gconf_client_get_string (gconf_client, KEY_OPEN_DIR, NULL);

	if (directory != NULL && *directory != 0) {
		locale_directory = g_filename_from_utf8 (directory, -1, NULL, NULL, NULL);
		if (!locale_directory || !g_file_test (locale_directory, G_FILE_TEST_EXISTS))
			locale_directory = g_strdup (directory);
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (file_chooser),
		                                     locale_directory);
		g_free (locale_directory);
	}

	response = gtk_dialog_run (GTK_DIALOG (file_chooser));

	if (response == GTK_RESPONSE_OK) {
		gchar *name;
		gchar *utf8_name = NULL;

		name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
		if (name) {
			gchar *dirname;

			utf8_name = g_filename_to_utf8 (name, -1, NULL, NULL, NULL);
			dirname = g_path_get_dirname (utf8_name);
			gconf_client_set_string (gconf_client, KEY_OPEN_DIR, dirname, NULL);
			g_free (dirname);
			g_free (utf8_name);

			if (window->priv->has_file == TRUE) {

				gsr_open_window (name);
			} else {

				g_object_set (G_OBJECT (window), "location", name, NULL);
				window->priv->dirty = FALSE;
			}

			g_free (name);
		}
    }

	gtk_widget_destroy (file_chooser);
	g_free (directory);
}
