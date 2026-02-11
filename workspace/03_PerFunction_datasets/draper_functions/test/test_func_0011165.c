lo_truncate(PGconn *conn, int fd, size_t len)
{
	PQArgBlock	argv[2];
	PGresult   *res;
	int			retval;
	int			result_len;

	if (conn->lobjfuncs == NULL)
	{
		if (lo_initialize(conn) < 0)
			return -1;
	}


	if (conn->lobjfuncs->fn_lo_truncate == 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
			libpq_gettext("cannot determine OID of function lo_truncate\n"));
		return -1;
	}

	argv[0].isint = 1;
	argv[0].len = 4;
	argv[0].u.integer = fd;

	argv[1].isint = 1;
	argv[1].len = 4;
	argv[1].u.integer = len;

	res = PQfn(conn, conn->lobjfuncs->fn_lo_truncate,
			   &retval, &result_len, 1, argv, 2);

	if (PQresultStatus(res) == PGRES_COMMAND_OK)
	{
		PQclear(res);
		return retval;
	}
	else
	{
		PQclear(res);
		return -1;
	}
}
