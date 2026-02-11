ecpg_autostart_transaction(struct statement * stmt)
{
	if (PQtransactionStatus(stmt->connection->connection) == PQTRANS_IDLE && !stmt->connection->autocommit)
	{
		stmt->results = PQexec(stmt->connection->connection, "begin transaction");
		if (!ecpg_check_PQresult(stmt->results, stmt->lineno, stmt->connection->connection, stmt->compat))
		{
			ecpg_free_params(stmt, false);
			return false;
		}
		PQclear(stmt->results);
		stmt->results = NULL;
	}
	return true;
}
