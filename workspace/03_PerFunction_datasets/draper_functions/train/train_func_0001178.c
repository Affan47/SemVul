gth_browser_activate_action_catalog_remove (GtkAction  *action,
					    GthBrowser *browser)
{
	GthFileData *file_data;
	GSettings   *settings;

	file_data = gth_browser_get_folder_popup_file_data (browser);

	settings = g_settings_new (GTHUMB_MESSAGES_SCHEMA);
	if (g_settings_get_boolean (settings, PREF_MSG_CONFIRM_DELETION)) {
		char      *prompt;
		GtkWidget *d;

		prompt = g_strdup_printf (_("Are you sure you want to remove \"%s\"?"), g_file_info_get_display_name (file_data->info));
		d = _gtk_message_dialog_new (GTK_WINDOW (browser),
					     GTK_DIALOG_MODAL,
					     GTK_STOCK_DIALOG_QUESTION,
					     prompt,
					     NULL,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					     GTK_STOCK_REMOVE, GTK_RESPONSE_YES,
					     NULL);
		g_signal_connect (d, "response", G_CALLBACK (remove_catalog_response_cb), file_data);
		gtk_widget_show (d);

		g_free (prompt);
	}
	else {
		remove_catalog (GTK_WINDOW (browser), file_data);
		g_object_unref (file_data);
	}

	g_object_unref (settings);
}
