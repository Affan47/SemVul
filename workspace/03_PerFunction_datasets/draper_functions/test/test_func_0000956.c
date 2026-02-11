_gda_sqlite_blob_op_new (SqliteConnectionData *cdata,
			 const gchar *db_name, const gchar *table_name,
			 const gchar *column_name, sqlite3_int64 rowid)
{
	GdaSqliteBlobOp *bop = NULL;
	int rc;
	sqlite3_blob *sblob;
	gchar *db, *table;
	gboolean free_strings = TRUE;
	gboolean transaction_started = FALSE;

	g_return_val_if_fail (table_name, NULL);
	g_return_val_if_fail (column_name, NULL);

	if (db_name) {
		db = (gchar *) db_name;
		table = (gchar *) table_name;
		free_strings = FALSE;
	}
	else if (! _split_identifier_string (g_strdup (table_name), &db, &table))
		return NULL;

	if (! _gda_sqlite_check_transaction_started (cdata->gdacnc, &transaction_started, NULL))
		return NULL;

	rc = SQLITE3_CALL (sqlite3_blob_open) (cdata->connection, db ? db : "main",
					       table, column_name, rowid,
				1,
				&(sblob));
	if (rc != SQLITE_OK) {
#ifdef GDA_DEBUG_NO
		g_print ("ERROR: %s\n", SQLITE3_CALL (sqlite3_errmsg) (cdata->connection));
#endif
		if (transaction_started)
			gda_connection_rollback_transaction (cdata->gdacnc, NULL, NULL);
		goto out;
	}

	bop = g_object_new (GDA_TYPE_SQLITE_BLOB_OP, NULL);
	bop->priv->sblob = sblob;
#ifdef GDA_DEBUG_NO
	g_print ("OPENED blob %p\n", bop);
#endif

 out:
	if (free_strings) {
		g_free (db);
		g_free (table);
	}
	return (GdaBlobOp*) bop;
}
