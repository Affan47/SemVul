getTransforms(Archive *fout, int *numTransforms)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	TransformInfo *transforminfo;
	int			i_tableoid;
	int			i_oid;
	int			i_trftype;
	int			i_trflang;
	int			i_trffromsql;
	int			i_trftosql;


	if (fout->remoteVersion < 90500)
	{
		*numTransforms = 0;
		return NULL;
	}

	query = createPQExpBuffer();


	selectSourceSchema(fout, "pg_catalog");

	appendPQExpBuffer(query, "SELECT tableoid, oid, "
					  "trftype, trflang, trffromsql::oid, trftosql::oid "
					  "FROM pg_transform "
					  "ORDER BY 3,4");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numTransforms = ntups;

	transforminfo = (TransformInfo *) pg_malloc(ntups * sizeof(TransformInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_trftype = PQfnumber(res, "trftype");
	i_trflang = PQfnumber(res, "trflang");
	i_trffromsql = PQfnumber(res, "trffromsql");
	i_trftosql = PQfnumber(res, "trftosql");

	for (i = 0; i < ntups; i++)
	{
		PQExpBufferData namebuf;
		TypeInfo   *typeInfo;
		char	   *lanname;

		transforminfo[i].dobj.objType = DO_TRANSFORM;
		transforminfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		transforminfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&transforminfo[i].dobj);
		transforminfo[i].trftype = atooid(PQgetvalue(res, i, i_trftype));
		transforminfo[i].trflang = atooid(PQgetvalue(res, i, i_trflang));
		transforminfo[i].trffromsql = atooid(PQgetvalue(res, i, i_trffromsql));
		transforminfo[i].trftosql = atooid(PQgetvalue(res, i, i_trftosql));


		initPQExpBuffer(&namebuf);
		typeInfo = findTypeByOid(transforminfo[i].trftype);
		lanname = get_language_name(fout, transforminfo[i].trflang);
		if (typeInfo && lanname)
			appendPQExpBuffer(&namebuf, "%s %s",
							  typeInfo->dobj.name, lanname);
		transforminfo[i].dobj.name = namebuf.data;
		free(lanname);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return transforminfo;
}
