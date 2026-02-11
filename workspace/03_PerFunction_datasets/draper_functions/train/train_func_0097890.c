reindex_all_databases(const char *host, const char *port,
					  const char *username, bool password,
					  const char *progname, bool echo, bool quiet)
{
	PGconn	   *conn;
	PGresult   *result;
	int			i;

	conn = connectDatabase("postgres", host, port, username, password, progname);
	result = executeQuery(conn, "SELECT datname FROM pg_database WHERE datallowconn;", progname, echo);
	PQfinish(conn);

	for (i = 0; i < PQntuples(result); i++)
	{
		char	   *dbname = PQgetvalue(result, i, 0);

		if (!quiet)
			fprintf(stderr, _("%s: reindexing database \"%s\"\n"), progname, dbname);

		reindex_one_database(dbname, dbname, "DATABASE", host, port, username,
							 password, progname, echo, quiet);
	}

	PQclear(result);
}
