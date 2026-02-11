e_book_backend_sqlitedb_set_contact_bdata (EBookBackendSqliteDB *ebsdb,
                                           const gchar *folderid,
                                           const gchar *uid,
                                           const gchar *value,
                                           GError **error)
{
	gchar *stmt = NULL;
	gboolean success;

	g_return_val_if_fail (E_IS_BOOK_BACKEND_SQLITEDB (ebsdb), FALSE);
	g_return_val_if_fail (folderid != NULL, FALSE);
	g_return_val_if_fail (uid != NULL, FALSE);
	g_return_val_if_fail (value != NULL, FALSE);

	LOCK_MUTEX (&ebsdb->priv->lock);

	if (!book_backend_sqlitedb_start_transaction (ebsdb, error)) {
		UNLOCK_MUTEX (&ebsdb->priv->lock);
		return FALSE;
	}

	stmt = sqlite3_mprintf (
		"UPDATE %Q SET bdata = %Q WHERE uid = %Q",
		folderid, value, uid);
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
