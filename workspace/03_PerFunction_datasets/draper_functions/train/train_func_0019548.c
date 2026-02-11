connectDatabase(const char *dbname, const char *pghost, const char *pgport,
	   const char *pguser, enum trivalue prompt_password, bool fail_on_error)
{
	PGconn	   *conn;
	bool		new_pass;
	const char *remoteversion_str;
	int			my_version;
	static char *password = NULL;

	if (prompt_password == TRI_YES && !password)
		password = simple_prompt("Password: ", 100, false);


	do
	{
		new_pass = false;
		conn = PQsetdbLogin(pghost, pgport, NULL, NULL, dbname, pguser, password);

		if (!conn)
		{
			fprintf(stderr, _("%s: could not connect to database \"%s\"\n"),
					progname, dbname);
			exit(1);
		}

		if (PQstatus(conn) == CONNECTION_BAD &&
			PQconnectionNeedsPassword(conn) &&
			password == NULL &&
			prompt_password != TRI_NO)
		{
			PQfinish(conn);
			password = simple_prompt("Password: ", 100, false);
			new_pass = true;
		}
	} while (new_pass);


	if (PQstatus(conn) == CONNECTION_BAD)
	{
		if (fail_on_error)
		{
			fprintf(stderr,
					_("%s: could not connect to database \"%s\": %s\n"),
					progname, dbname, PQerrorMessage(conn));
			exit(1);
		}
		else
		{
			PQfinish(conn);
			return NULL;
		}
	}

	remoteversion_str = PQparameterStatus(conn, "server_version");
	if (!remoteversion_str)
	{
		fprintf(stderr, _("%s: could not get server version\n"), progname);
		exit(1);
	}
	server_version = parse_version(remoteversion_str);
	if (server_version < 0)
	{
		fprintf(stderr, _("%s: could not parse server version \"%s\"\n"),
				progname, remoteversion_str);
		exit(1);
	}

	my_version = parse_version(PG_VERSION);
	if (my_version < 0)
	{
		fprintf(stderr, _("%s: could not parse version \"%s\"\n"),
				progname, PG_VERSION);
		exit(1);
	}


	if (my_version != server_version
		&& (server_version < 70000 ||
			(server_version / 100) > (my_version / 100)))
	{
		fprintf(stderr, _("server version: %s; %s version: %s\n"),
				remoteversion_str, progname, PG_VERSION);
		fprintf(stderr, _("aborting because of server version mismatch\n"));
		exit(1);
	}


	if (server_version >= 70300)
		executeCommand(conn, "SET search_path = pg_catalog");

	return conn;
}
