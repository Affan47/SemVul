on_destination_dialog_response (GtkDialog *dialog,
				gint       response_id,
				gpointer   user_data)
{
	CopyCallbackData *copy_data = user_data;

	if (response_id == GTK_RESPONSE_OK) {
		char *target_uri;
		GList *uris, *l;

		target_uri = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (dialog));

		uris = NULL;
		for (l = copy_data->selection; l != NULL; l = l->next) {
			uris = g_list_prepend (uris,
					       nautilus_file_get_uri ((NautilusFile *) l->data));
		}
		uris = g_list_reverse (uris);

		nautilus_view_move_copy_items (copy_data->view, uris, NULL, target_uri,
					       copy_data->is_move ? GDK_ACTION_MOVE : GDK_ACTION_COPY,
					       0, 0);

		g_list_free_full (uris, g_free);
		g_free (target_uri);
	}

	copy_data_free (copy_data);
	gtk_widget_destroy (GTK_WIDGET (dialog));
}
