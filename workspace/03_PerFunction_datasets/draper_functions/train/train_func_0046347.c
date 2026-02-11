convertTSFunction(Oid funcOid)
{
	char	   *result;
	char		query[128];
	PGresult   *res;
	int			ntups;

	snprintf(query, sizeof(query),
			 "SELECT '%u'::pg_catalog.regproc", funcOid);
	res = PQexec(g_conn, query);
	check_sql_result(res, g_conn, query, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	if (ntups != 1)
	{
		write_msg(NULL, "query returned %d rows instead of one: %s\n",
				  ntups, query);
		exit_nicely();
	}

	result = strdup(PQgetvalue(res, 0, 0));

	PQclear(res);

	return result;
}
