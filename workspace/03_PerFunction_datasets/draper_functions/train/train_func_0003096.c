dumpEnumType(Archive *fout, TypeInfo *tinfo)
{
	PQExpBuffer q = createPQExpBuffer();
	PQExpBuffer delq = createPQExpBuffer();
	PQExpBuffer query = createPQExpBuffer();
	PGresult   *res;
	int			num,
				i;
	char	   *label;


	selectSourceSchema(tinfo->dobj.namespace->dobj.name);

	appendPQExpBuffer(query, "SELECT enumlabel FROM pg_catalog.pg_enum "
					  "WHERE enumtypid = '%u'"
					  "ORDER BY oid",
					  tinfo->dobj.catId.oid);

	res = PQexec(g_conn, query->data);
	check_sql_result(res, g_conn, query->data, PGRES_TUPLES_OK);

	num = PQntuples(res);

	if (num == 0)
	{
		write_msg(NULL, "no label definitions found for enum ID %u\n", tinfo->dobj.catId.oid);
		exit_nicely();
	}


	appendPQExpBuffer(delq, "DROP TYPE %s.",
					  fmtId(tinfo->dobj.namespace->dobj.name));
	appendPQExpBuffer(delq, "%s;\n",
					  fmtId(tinfo->dobj.name));
	appendPQExpBuffer(q, "CREATE TYPE %s AS ENUM (\n",
					  fmtId(tinfo->dobj.name));
	for (i = 0; i < num; i++)
	{
		label = PQgetvalue(res, i, 0);
		if (i > 0)
			appendPQExpBuffer(q, ",\n");
		appendPQExpBuffer(q, "    ");
		appendStringLiteralAH(q, label, fout);
	}
	appendPQExpBuffer(q, "\n);\n");

	ArchiveEntry(fout, tinfo->dobj.catId, tinfo->dobj.dumpId,
				 tinfo->dobj.name,
				 tinfo->dobj.namespace->dobj.name,
				 NULL,
				 tinfo->rolname, false,
				 "TYPE", q->data, delq->data, NULL,
				 tinfo->dobj.dependencies, tinfo->dobj.nDeps,
				 NULL, NULL);


	resetPQExpBuffer(q);

	appendPQExpBuffer(q, "TYPE %s", fmtId(tinfo->dobj.name));
	dumpComment(fout, q->data,
				tinfo->dobj.namespace->dobj.name, tinfo->rolname,
				tinfo->dobj.catId, 0, tinfo->dobj.dumpId);

	PQclear(res);
	destroyPQExpBuffer(q);
	destroyPQExpBuffer(delq);
	destroyPQExpBuffer(query);
}
