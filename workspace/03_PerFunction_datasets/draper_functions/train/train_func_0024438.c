pk_transaction_db_print (PkTransactionDb *tdb)
{
	const gchar *statement;

	g_return_val_if_fail (PK_IS_TRANSACTION_DB (tdb), FALSE);

	statement = "SELECT transaction_id, timespec, succeeded, duration, role FROM transactions";
	pk_transaction_db_sql_statement (tdb, statement);

	return TRUE;
}
