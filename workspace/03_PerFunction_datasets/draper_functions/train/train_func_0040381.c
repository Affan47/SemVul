open_file_cb (GtkAction *action,
	      gpointer   user_data)
{
	GtkWidget *chooser;
	gint response;
	static gchar *last_dir;

	g_return_if_fail (GTK_SOURCE_IS_BUFFER (user_data));

	chooser = gtk_file_chooser_dialog_new ("Open file...",
					       NULL,
					       GTK_FILE_CHOOSER_ACTION_OPEN,
					       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					       GTK_STOCK_OPEN, GTK_RESPONSE_OK,
					       NULL);

	if (last_dir == NULL)
	{
		last_dir = g_strdup (TOP_SRCDIR "/gtksourceview");
	}

	if (last_dir != NULL && g_path_is_absolute (last_dir))
	{
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser),
						     last_dir);
	}

	response = gtk_dialog_run (GTK_DIALOG (chooser));

	if (response == GTK_RESPONSE_OK)
	{
		gchar *filename;

		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));

		if (filename != NULL)
		{
			g_free (last_dir);
			last_dir = gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER (chooser));
			open_file (GTK_SOURCE_BUFFER (user_data), filename);
			g_free (filename);
		}
	}

	gtk_widget_destroy (chooser);
}
