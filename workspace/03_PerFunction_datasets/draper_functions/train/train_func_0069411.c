getFormattedTypeName(Archive *fout, Oid oid, OidOptions opts)
{
	char	   *result;
	PQExpBuffer query;
	PGresult   *res;

	if (oid == 0)
	{
		if ((opts & zeroAsOpaque) != 0)
			return pg_strdup(g_opaque_type);
		else if ((opts & zeroAsAny) != 0)
			return pg_strdup("'any'");
		else if ((opts & zeroAsStar) != 0)
			return pg_strdup("*");
		else if ((opts & zeroAsNone) != 0)
			return pg_strdup("NONE");
	}

	query = createPQExpBuffer();
	if (fout->remoteVersion >= 70300)
	{
		appendPQExpBuffer(query, "SELECT pg_catalog.format_type('%u'::pg_catalog.oid, NULL)",
						  oid);
	}
	else if (fout->remoteVersion >= 70100)
	{
		appendPQExpBuffer(query, "SELECT format_type('%u'::oid, NULL)",
						  oid);
	}
	else
	{
		appendPQExpBuffer(query, "SELECT typname "
						  "FROM pg_type "
						  "WHERE oid = '%u'::oid",
						  oid);
	}

	res = ExecuteSqlQueryForSingleRow(fout, query->data);

	if (fout->remoteVersion >= 70100)
	{

		result = pg_strdup(PQgetvalue(res, 0, 0));
	}
	else
	{

		result = pg_strdup(fmtId(PQgetvalue(res, 0, 0)));
	}

	PQclear(res);
	destroyPQExpBuffer(query);

	return result;
}
