GUI_file_chooser_dialog_response_h (GtkDialog *dialog,
										int response_id,
										gpointer user_data)
	{
		int accept_id = GPOINTER_TO_INT (user_data);
		if (response_id == accept_id) {
			char *uri;
			uri = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER(dialog));
			if (uri)
				g_free(uri);
			else
				g_signal_stop_emission_by_name (dialog, "response");
		}
	}
