function_property_names (sqlite3_context *context,
                         int              argc,
                         sqlite3_value   *argv[])
{
	static gchar **names = NULL;
	static gsize names_initialized = 0;

	if (g_once_init_enter (&names_initialized)) {
		GPtrArray *names_array;
		sqlite3_stmt *stmt;
		sqlite3 *db;
		int rc;

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
			}
		}

		if (rc == SQLITE_DONE) {
			rc = sqlite3_finalize (stmt);
		}

		names = (gchar **) g_ptr_array_free (names_array, FALSE);
		g_once_init_leave (&names_initialized, (rc == SQLITE_OK));
	}

	sqlite3_result_blob (context, names, sizeof (names), NULL);
}
