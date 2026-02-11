reindex_system_catalogs(const char *dbname, const char *host, const char *port,
						const char *username, enum trivalue prompt_password,
						const char *progname, bool echo)
{
	PQExpBufferData sql;

	PGconn	   *conn;

	initPQExpBuffer(&sql);

	appendPQExpBuffer(&sql, "REINDEX SYSTEM %s;\n", dbname);

	conn = connectDatabase(dbname, host, port, username, prompt_password, progname);
	if (!executeMaintenanceCommand(conn, sql.data, echo))
	{
		fprintf(stderr, _("%s: reindexing of system catalogs failed: %s"),
				progname, PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}
	PQfinish(conn);
	termPQExpBuffer(&sql);
}
