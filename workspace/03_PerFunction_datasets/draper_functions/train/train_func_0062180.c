pgsql_db_query_ret(PGconn *pgsql_db, char *query)
{
	PGresult *result = NULL;

	if (!pgsql_db)
		fatal("You haven't inited this storage yet.");

	result = PQexec(pgsql_db, query);

	if (PQresultStatus(result) != PGRES_COMMAND_OK
	    && PQresultStatus(result) != PGRES_TUPLES_OK) {
		error("PQexec failed: %d %s", PQresultStatus(result),
		      PQerrorMessage(pgsql_db));
		info("query was %s", query);
		PQclear(result);
		return NULL;
	}
	return result;
}
