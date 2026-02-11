camel_db_begin_transaction (CamelDB *cdb,
                            GError **error)
{
	if (!cdb)
		return -1;

	WRITER_LOCK (cdb);
	STARTTS ("BEGIN");

	cdb->priv->transaction_is_on = TRUE;

	return (cdb_sql_exec (cdb->db, "BEGIN", NULL, NULL, error));
}
