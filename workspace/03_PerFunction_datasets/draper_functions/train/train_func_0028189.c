getForeignServers(int *numForeignServers)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	ForeignServerInfo *srvinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_srvname;
	int			i_rolname;
	int			i_srvfdw;
	int			i_srvtype;
	int			i_srvversion;
	int			i_srvacl;
	int			i_srvoptions;


	if (g_fout->remoteVersion < 80400)
	{
		*numForeignServers = 0;
		return NULL;
	}


	selectSourceSchema("pg_catalog");

	appendPQExpBuffer(query, "SELECT tableoid, oid, srvname, "
					  "(%s srvowner) AS rolname, "
					  "srvfdw, srvtype, srvversion, srvacl,"
					  "array_to_string(ARRAY("
		 "		SELECT option_name || ' ' || quote_literal(option_value) "
	   "		FROM pg_options_to_table(srvoptions)), ', ') AS srvoptions "
					  "FROM pg_foreign_server",
					  username_subquery);

	res = PQexec(g_conn, query->data);
	check_sql_result(res, g_conn, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numForeignServers = ntups;

	srvinfo = (ForeignServerInfo *) malloc(ntups * sizeof(ForeignServerInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_srvname = PQfnumber(res, "srvname");
	i_rolname = PQfnumber(res, "rolname");
	i_srvfdw = PQfnumber(res, "srvfdw");
	i_srvtype = PQfnumber(res, "srvtype");
	i_srvversion = PQfnumber(res, "srvversion");
	i_srvacl = PQfnumber(res, "srvacl");
	i_srvoptions = PQfnumber(res, "srvoptions");

	for (i = 0; i < ntups; i++)
	{
		srvinfo[i].dobj.objType = DO_FOREIGN_SERVER;
		srvinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		srvinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&srvinfo[i].dobj);
		srvinfo[i].dobj.name = strdup(PQgetvalue(res, i, i_srvname));
		srvinfo[i].dobj.namespace = NULL;
		srvinfo[i].rolname = strdup(PQgetvalue(res, i, i_rolname));
		srvinfo[i].srvfdw = atooid(PQgetvalue(res, i, i_srvfdw));
		srvinfo[i].srvtype = strdup(PQgetvalue(res, i, i_srvtype));
		srvinfo[i].srvversion = strdup(PQgetvalue(res, i, i_srvversion));
		srvinfo[i].srvoptions = strdup(PQgetvalue(res, i, i_srvoptions));
		srvinfo[i].srvacl = strdup(PQgetvalue(res, i, i_srvacl));


		selectDumpableObject(&(srvinfo[i].dobj));
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return srvinfo;
}
