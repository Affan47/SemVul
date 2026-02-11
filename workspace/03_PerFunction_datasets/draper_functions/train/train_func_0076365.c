e_book_backend_sqlitedb_set_revision (EBookBackendSqliteDB *ebsdb,
                                      const gchar *folderid,
                                      const gchar *revision,
                                      GError **error)
{
	gchar *stmt = NULL;
	gboolean success;

	g_return_val_if_fail (E_IS_BOOK_BACKEND_SQLITEDB (ebsdb), FALSE);
	g_return_val_if_fail (folderid && folderid[0], FALSE);

	LOCK_MUTEX (&ebsdb->priv->lock);

	if (!book_backend_sqlitedb_start_transaction (ebsdb, error)) {
		UNLOCK_MUTEX (&ebsdb->priv->lock);
		return FALSE;
	}

	stmt = sqlite3_mprintf (
		"UPDATE folders SET revision = %Q "
		"WHERE folder_id = %Q", revision, folderid);
	success = book_backend_sql_exec (
		ebsdb->priv->db, stmt, NULL, NULL, error);
	sqlite3_free (stmt);

	if (success)
		success = book_backend_sqlitedb_commit_transaction (ebsdb, error);
	else

		book_backend_sqlitedb_rollback_transaction (ebsdb, NULL);

	UNLOCK_MUTEX (&ebsdb->priv->lock);

	return success;
}
