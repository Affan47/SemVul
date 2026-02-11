gfarm_pgsql_start_with_retry(const char *diag)
{
	PGresult *res;

	if (transaction_nesting++ > 0)
		return (GFARM_ERR_NO_ERROR);

	transaction_ok = 1;
	do {
		res = PQexec(conn, "START TRANSACTION");
	} while (PQresultStatus(res) != PGRES_COMMAND_OK &&
	    pgsql_should_retry(res));
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		gflog_error(GFARM_MSG_1000428, "%s transaction BEGIN: %s",
		    diag, PQresultErrorMessage(res));
		PQclear(res);
		return (GFARM_ERR_UNKNOWN);
	}
	PQclear(res);
	return (GFARM_ERR_NO_ERROR);
}
