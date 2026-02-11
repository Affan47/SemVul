edit_done_cb (NMConnectionEditor *editor, GtkResponseType response, gpointer user_data)
{
	NMConnectionList *list = user_data;

	if (response == GTK_RESPONSE_OK) {
		NMRemoteConnection *connection = NM_REMOTE_CONNECTION (nm_connection_editor_get_connection (editor));
		GtkTreeIter iter;

		if (get_iter_for_connection (list, connection, &iter))
			update_connection_row (list, &iter, connection);
	}

	g_object_unref (editor);
	g_signal_emit (list, list_signals[EDITING_DONE], 0, 0);
}
