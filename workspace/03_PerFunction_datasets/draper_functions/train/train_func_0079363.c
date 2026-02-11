libpqConnect(const char *connstr)
{
	char	   *str;

	conn = PQconnectdb(connstr);
	if (PQstatus(conn) == CONNECTION_BAD)
		pg_fatal("could not connect to server: %s",
				 PQerrorMessage(conn));

	pg_log(PG_PROGRESS, "connected to server\n");


	str = run_simple_query("SELECT pg_is_in_recovery()");
	if (strcmp(str, "f") != 0)
		pg_fatal("source server must not be in recovery mode\n");
	pg_free(str);


	str = run_simple_query("SHOW full_page_writes");
	if (strcmp(str, "on") != 0)
		pg_fatal("full_page_writes must be enabled in the source server\n");
	pg_free(str);
}
