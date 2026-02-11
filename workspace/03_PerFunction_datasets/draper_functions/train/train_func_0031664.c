getConstraints(Archive *fout, TableInfo tblinfo[], int numTables)
{
	int			i,
				j;
	ConstraintInfo *constrinfo;
	PQExpBuffer query;
	PGresult   *res;
	int			i_contableoid,
				i_conoid,
				i_conname,
				i_confrelid,
				i_condef;
	int			ntups;


	if (fout->remoteVersion < 70300)
		return;

	query = createPQExpBuffer();

	for (i = 0; i < numTables; i++)
	{
		TableInfo  *tbinfo = &tblinfo[i];

		if (!tbinfo->hastriggers || !tbinfo->dobj.dump)
			continue;

		if (g_verbose)
			write_msg(NULL, "reading foreign key constraints for table \"%s.%s\"\n",
					  tbinfo->dobj.namespace->dobj.name,
					  tbinfo->dobj.name);


		selectSourceSchema(fout, tbinfo->dobj.namespace->dobj.name);

		resetPQExpBuffer(query);
		appendPQExpBuffer(query,
						  "SELECT tableoid, oid, conname, confrelid, "
						  "pg_catalog.pg_get_constraintdef(oid) AS condef "
						  "FROM pg_catalog.pg_constraint "
						  "WHERE conrelid = '%u'::pg_catalog.oid "
						  "AND contype = 'f'",
						  tbinfo->dobj.catId.oid);
		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

		ntups = PQntuples(res);

		i_contableoid = PQfnumber(res, "tableoid");
		i_conoid = PQfnumber(res, "oid");
		i_conname = PQfnumber(res, "conname");
		i_confrelid = PQfnumber(res, "confrelid");
		i_condef = PQfnumber(res, "condef");

		constrinfo = (ConstraintInfo *) pg_malloc(ntups * sizeof(ConstraintInfo));

		for (j = 0; j < ntups; j++)
		{
			constrinfo[j].dobj.objType = DO_FK_CONSTRAINT;
			constrinfo[j].dobj.catId.tableoid = atooid(PQgetvalue(res, j, i_contableoid));
			constrinfo[j].dobj.catId.oid = atooid(PQgetvalue(res, j, i_conoid));
			AssignDumpId(&constrinfo[j].dobj);
			constrinfo[j].dobj.name = pg_strdup(PQgetvalue(res, j, i_conname));
			constrinfo[j].dobj.namespace = tbinfo->dobj.namespace;
			constrinfo[j].contable = tbinfo;
			constrinfo[j].condomain = NULL;
			constrinfo[j].contype = 'f';
			constrinfo[j].condef = pg_strdup(PQgetvalue(res, j, i_condef));
			constrinfo[j].confrelid = atooid(PQgetvalue(res, j, i_confrelid));
			constrinfo[j].conindex = 0;
			constrinfo[j].condeferrable = false;
			constrinfo[j].condeferred = false;
			constrinfo[j].conislocal = true;
			constrinfo[j].separate = true;
		}

		PQclear(res);
	}

	destroyPQExpBuffer(query);
}
