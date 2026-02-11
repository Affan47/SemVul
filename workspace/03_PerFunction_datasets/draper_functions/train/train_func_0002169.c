tracker_data_query_rdf_type (gint id)
{
	TrackerDBCursor *cursor = NULL;
	TrackerDBInterface *iface;
	TrackerDBStatement *stmt;
	GPtrArray *ret = NULL;
	GError *error = NULL;

	iface = tracker_db_manager_get_db_interface ();

	stmt = tracker_db_interface_create_statement (iface, TRACKER_DB_STATEMENT_CACHE_TYPE_SELECT, &error,
	                                              "SELECT (SELECT Uri FROM Resource WHERE ID = \"rdf:type\") "
	                                              "FROM \"rdfs:Resource_rdf:type\" "
	                                              "WHERE ID = ?");

	if (stmt) {
		tracker_db_statement_bind_int (stmt, 0, id);
		cursor = tracker_db_statement_start_cursor (stmt, &error);
		g_object_unref (stmt);
	}

	if (cursor) {


		ret = g_ptr_array_sized_new (20);
		while (tracker_db_cursor_iter_next (cursor, NULL, &error)) {
			const gchar *class_uri;
			TrackerClass *cl;

			class_uri = tracker_db_cursor_get_string (cursor, 0, NULL);
			cl = tracker_ontologies_get_class_by_uri (class_uri);
			if (!cl) {
				g_critical ("Unknown class %s", class_uri);
				continue;
			}
			g_ptr_array_add (ret, cl);
		}
		g_object_unref (cursor);
	}

	if (G_UNLIKELY (error)) {
		g_critical ("Could not query RDF type: %s\n", error->message);
		g_error_free (error);

		if (ret) {
			g_ptr_array_free (ret, FALSE);
			ret = NULL;
		}
	}

	return ret;
}
