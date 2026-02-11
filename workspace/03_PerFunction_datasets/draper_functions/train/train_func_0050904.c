expand_schema_name_patterns(Archive *fout,
							SimpleStringList *patterns,
							SimpleOidList *oids,
							bool strict_names)
{
	PQExpBuffer query;
	PGresult   *res;
	SimpleStringListCell *cell;
	int			i;

	if (patterns->head == NULL)
		return;

	if (fout->remoteVersion < 70300)
		exit_horribly(NULL, "server version must be at least 7.3 to use schema selection switches\n");

	query = createPQExpBuffer();


	for (cell = patterns->head; cell; cell = cell->next)
	{
		appendPQExpBuffer(query,
						  "SELECT oid FROM pg_catalog.pg_namespace n\n");
		processSQLNamePattern(GetConnection(fout), query, cell->val, false,
							  false, NULL, "n.nspname", NULL, NULL);

		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);
		if (strict_names && PQntuples(res) == 0)
			exit_horribly(NULL, "No matching table(s) were found for pattern \"%s\"\n", cell->val);

		for (i = 0; i < PQntuples(res); i++)
		{
			simple_oid_list_append(oids, atooid(PQgetvalue(res, i, 0)));
		}

		PQclear(res);
		resetPQExpBuffer(query);
	}

	destroyPQExpBuffer(query);
}
