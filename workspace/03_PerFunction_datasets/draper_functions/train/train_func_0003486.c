meta_data_sqlite_cache_destroy(void)
{
	unsigned i;
	for (i = 0; i < G_N_ELEMENTS(meta_data_sqlite_stmt); ++i) {
		g_assert(meta_data_sqlite_stmt[i] != NULL);

		sqlite3_finalize(meta_data_sqlite_stmt[i]);
	}
	sqlite3_close(meta_data_sqlite_db);
}
