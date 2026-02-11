do_connect(char *dbname, char *user, char *host, char *port)
{
	PGconn	   *o_conn = pset.db,
			   *n_conn;
	char	   *password = NULL;

	if (!dbname)
		dbname = PQdb(o_conn);
	if (!user)
		user = PQuser(o_conn);
	if (!host)
		host = PQhost(o_conn);
	if (!port)
		port = PQport(o_conn);


	if (pset.getPassword == TRI_YES)
	{
		password = prompt_for_password(user);
	}
	else if (o_conn && user && strcmp(PQuser(o_conn), user) == 0)
	{
		password = strdup(PQpass(o_conn));
	}

	while (true)
	{
		n_conn = PQsetdbLogin(host, port, NULL, NULL,
							  dbname, user, password);


		if (password)
			free(password);

		if (PQstatus(n_conn) == CONNECTION_OK)
			break;


		if (!password && PQconnectionNeedsPassword(n_conn) && pset.getPassword != TRI_NO)
		{
			PQfinish(n_conn);
			password = prompt_for_password(user);
			continue;
		}


		if (pset.cur_cmd_interactive)
		{
			psql_error("%s", PQerrorMessage(n_conn));


			if (o_conn)
				fputs(_("Previous connection kept\n"), stderr);
		}
		else
		{
			psql_error("\\connect: %s", PQerrorMessage(n_conn));
			if (o_conn)
			{
				PQfinish(o_conn);
				pset.db = NULL;
			}
		}

		PQfinish(n_conn);
		return false;
	}


	PQsetNoticeProcessor(n_conn, NoticeProcessor, NULL);
	pset.db = n_conn;
	SyncVariables();
	connection_warnings();


	if (!pset.quiet)
	{
		printf(_("You are now connected to database \"%s\""), PQdb(pset.db));

		if (param_is_newly_set(PQhost(o_conn), PQhost(pset.db)))
			printf(_(" on host \"%s\""), PQhost(pset.db));

		if (param_is_newly_set(PQport(o_conn), PQport(pset.db)))
			printf(_(" at port \"%s\""), PQport(pset.db));

		if (param_is_newly_set(PQuser(o_conn), PQuser(pset.db)))
			printf(_(" as user \"%s\""), PQuser(pset.db));

		printf(".\n");
	}

	if (o_conn)
		PQfinish(o_conn);
	return true;
}
