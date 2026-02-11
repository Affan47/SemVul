mime_types_cb (GObject      *object,
               GAsyncResult *result,
               gpointer      user_data)
{
	MimeTypesData *mtd = user_data;
	TrackerSparqlCursor *cursor;
	GError *error = NULL;

	cursor = tracker_sparql_connection_query_finish (TRACKER_SPARQL_CONNECTION (object),
	                                                 result,
	                                                 &error);

	if (cursor) {
		tracker_dbus_request_comment (mtd->request,
		                              "Found files that will need reindexing");

		while (tracker_sparql_cursor_next (cursor, NULL, NULL)) {
			GFile *file;
			const gchar *url;

			url = tracker_sparql_cursor_get_string (cursor, 0, NULL);
			file = g_file_new_for_uri (url);
			tracker_miner_fs_check_file (TRACKER_MINER_FS (mtd->miner_files), file, FALSE);
			g_object_unref (file);
		}

		tracker_dbus_request_end (mtd->request, NULL);
		g_dbus_method_invocation_return_value (mtd->invocation, NULL);
	} else {
		tracker_dbus_request_end (mtd->request, error);
		g_dbus_method_invocation_return_gerror (mtd->invocation, error);
	}

	mime_types_data_destroy (user_data);
}
