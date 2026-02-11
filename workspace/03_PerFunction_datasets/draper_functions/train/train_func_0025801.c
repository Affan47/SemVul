ConnectDatabase(Archive *AHX,
				const char *dbname,
				const char *pghost,
				const char *pgport,
				const char *username,
				const int reqPwd,
				const int ignoreVersion)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	char	   *password = NULL;
	bool		need_pass = false;

	if (AH->connection)
		die_horribly(AH, modulename, "already connected to a database\n");

	if (reqPwd)
	{
		password = simple_prompt("Password: ", 100, false);
		if (password == NULL)
			die_horribly(AH, modulename, "out of memory\n");
		AH->requirePassword = true;
	}
	else
		AH->requirePassword = false;


	do
	{
		need_pass = false;
		AH->connection = PQsetdbLogin(pghost, pgport, NULL, NULL,
									  dbname, username, password);

		if (!AH->connection)
			die_horribly(AH, modulename, "failed to connect to database\n");

		if (PQstatus(AH->connection) == CONNECTION_BAD &&
		 strcmp(PQerrorMessage(AH->connection), PQnoPasswordSupplied) == 0 &&
			!feof(stdin))
		{
			PQfinish(AH->connection);
			need_pass = true;
			free(password);
			password = NULL;
			password = simple_prompt("Password: ", 100, false);
		}
	} while (need_pass);

	if (password)
		free(password);


	if (PQstatus(AH->connection) == CONNECTION_BAD)
		die_horribly(AH, modulename, "connection to database \"%s\" failed: %s",
					 PQdb(AH->connection), PQerrorMessage(AH->connection));


	_check_database_version(AH, ignoreVersion);

	PQsetNoticeProcessor(AH->connection, notice_processor, NULL);

	return AH->connection;
}
