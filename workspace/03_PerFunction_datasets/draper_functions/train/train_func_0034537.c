function_property_names (sqlite3_context *context,
                         int              argc,
                         sqlite3_value   *argv[])
{
	static gchar **names = NULL;
	static GMutex mutex;
	int rc = SQLITE_DONE;

	g_mutex_lock (&mutex);

	if (G_UNLIKELY (names == NULL)) {
		GPtrArray *names_array;
		sqlite3_stmt *stmt;
		sqlite3 *db;

		names_array = g_ptr_array_new ();
		db = sqlite3_context_db_handle (context);
		rc = sqlite3_prepare_v2 (db,
		                         "SELECT Uri "
		                         "FROM Resource "
		                         "JOIN \"rdf:Property\" "
		                         "ON Resource.ID = \"rdf:Property\".ID "
		                         "WHERE \"rdf:Property\".\"tracker:fulltextIndexed\" = 1 "
		                         "ORDER BY \"rdf:Property\".ID ",
		                         -1, &stmt, NULL);

		while ((rc = sqlite3_step (stmt)) != SQLITE_DONE) {
			if (rc == SQLITE_ROW) {
				const gchar *name;

				name = sqlite3_column_text (stmt, 0);
				g_ptr_array_add (names_array, g_strdup (name));
			} else if (rc != SQLITE_BUSY) {
				break;
			}
		}

		sqlite3_finalize (stmt);

		if (rc == SQLITE_DONE) {
			names = (gchar **) g_ptr_array_free (names_array, FALSE);
		} else {
			g_ptr_array_free (names_array, TRUE);
		}
	}

	g_mutex_unlock (&mutex);

	if (rc == SQLITE_DONE)
		sqlite3_result_blob (context, names, sizeof (names), NULL);
	else
		sqlite3_result_error_code (context, rc);
}
