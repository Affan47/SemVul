ECPGsetcommit(int lineno, const char *mode, const char *connection_name)
{
	struct connection *con = ecpg_get_connection(connection_name);
	PGresult   *results;

	if (!ecpg_init(con, connection_name, lineno))
		return (false);

	ecpg_log("ECPGsetcommit on line %d: action \"%s\"; connection \"%s\"\n", lineno, mode, con->name);

	if (con->autocommit && strncmp(mode, "off", strlen("off")) == 0)
	{
		if (PQtransactionStatus(con->connection) == PQTRANS_IDLE)
		{
			results = PQexec(con->connection, "begin transaction");
			if (!ecpg_check_PQresult(results, lineno, con->connection, ECPG_COMPAT_PGSQL))
				return false;
			PQclear(results);
		}
		con->autocommit = false;
	}
	else if (!con->autocommit && strncmp(mode, "on", strlen("on")) == 0)
	{
		if (PQtransactionStatus(con->connection) != PQTRANS_IDLE)
		{
			results = PQexec(con->connection, "commit");
			if (!ecpg_check_PQresult(results, lineno, con->connection, ECPG_COMPAT_PGSQL))
				return false;
			PQclear(results);
		}
		con->autocommit = true;
	}

	return true;
}
