new_folder_dialog_response_cb (GtkWidget *dialog,
			       int        response_id,
			       gpointer   user_data)
{
	NewFolderData *data = user_data;
	char          *name;
	GFile         *folder;
	GError        *error = NULL;

	if (response_id != GTK_RESPONSE_OK) {
		new_fodler_data_free (data);
		gtk_widget_destroy (dialog);
		return;
	}

	name = gth_request_dialog_get_normalized_text (GTH_REQUEST_DIALOG (dialog));
	if (_g_utf8_all_spaces (name)) {
		g_free (name);
		gth_request_dialog_set_info_text (GTH_REQUEST_DIALOG (dialog), GTK_MESSAGE_ERROR, _("No name specified"));
		return;
	}

	if (g_regex_match_simple ("/", name, 0, 0)) {
		char *message;

		message = g_strdup_printf (_("Invalid name. The following characters are not allowed: %s"), "/");
		gth_request_dialog_set_info_text (GTH_REQUEST_DIALOG (dialog), GTK_MESSAGE_ERROR, message);

		g_free (message);
		g_free (name);

		return;
	}

	folder = g_file_get_child_for_display_name (data->parent, name, &error);
	if ((folder != NULL) && g_file_make_directory (folder, NULL, &error)) {
		GList       *list;
		GtkWidget   *folder_tree;
		GtkTreePath *path;

		list = g_list_prepend (NULL, folder);
		gth_monitor_folder_changed (gth_main_get_default_monitor (),
					    data->parent,
					    list,
					    GTH_MONITOR_EVENT_CREATED);

		folder_tree = gth_browser_get_folder_tree (data->browser);
		path = gth_folder_tree_get_path (GTH_FOLDER_TREE (folder_tree), data->parent);
		gth_folder_tree_expand_row (GTH_FOLDER_TREE (folder_tree), path, FALSE);

		gtk_tree_path_free (path);
		g_list_free (list);
	}

	if (error != NULL) {
		if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_EXISTS))
			gth_request_dialog_set_info_text (GTH_REQUEST_DIALOG (dialog), GTK_MESSAGE_ERROR, _("Name already used"));
		else
			gth_request_dialog_set_info_text (GTH_REQUEST_DIALOG (dialog), GTK_MESSAGE_ERROR, error->message);
		g_clear_error (&error);
	}
	else {
		new_fodler_data_free (data);
		gtk_widget_destroy (dialog);
	}

	g_object_unref (folder);
}
