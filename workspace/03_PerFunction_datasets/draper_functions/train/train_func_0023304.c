class_add_domain_indexes_from_db (TrackerDBInterface *iface,
                                  TrackerClass       *class)
{
	TrackerDBStatement *stmt;
	TrackerDBCursor *cursor;
	GError *error = NULL;

	stmt = tracker_db_interface_create_statement (iface, TRACKER_DB_STATEMENT_CACHE_TYPE_SELECT, &error,
	                                              "SELECT (SELECT Uri FROM Resource WHERE ID = \"tracker:domainIndex\") "
	                                              "FROM \"rdfs:Class_tracker:domainIndex\" "
	                                              "WHERE ID = (SELECT ID FROM Resource WHERE Uri = ?)");

	if (!stmt) {
		g_critical ("%s", error->message);
		g_error_free (error);
		return;
	}

	tracker_db_statement_bind_text (stmt, 0, tracker_class_get_uri (class));
	cursor = tracker_db_statement_start_cursor (stmt, NULL);
	g_object_unref (stmt);

	if (cursor) {
		while (tracker_db_cursor_iter_next (cursor, NULL, NULL)) {
			TrackerProperty *domain_index;
			const gchar *domain_index_uri;

			domain_index_uri = tracker_db_cursor_get_string (cursor, 0, NULL);
			domain_index = tracker_ontologies_get_property_by_uri (domain_index_uri);
			tracker_class_add_domain_index (class, domain_index);
			tracker_property_add_domain_index (domain_index, class);
		}

		g_object_unref (cursor);
	}
}
