PQsendQueryPrepared(PGconn *conn,
					const char *stmtName,
					int nParams,
					const char *const * paramValues,
					const int *paramLengths,
					const int *paramFormats,
					int resultFormat)
{
	if (!PQsendQueryStart(conn))
		return 0;


	if (!stmtName)
	{
		printfPQExpBuffer(&conn->errorMessage,
						libpq_gettext("statement name is a null pointer\n"));
		return 0;
	}
	if (nParams < 0 || nParams > 65535)
	{
		printfPQExpBuffer(&conn->errorMessage,
		libpq_gettext("number of parameters must be between 0 and 65535\n"));
		return 0;
	}

	return PQsendQueryGuts(conn,
						   NULL,
						   stmtName,
						   nParams,
						   NULL,
						   paramValues,
						   paramLengths,
						   paramFormats,
						   resultFormat);
}
