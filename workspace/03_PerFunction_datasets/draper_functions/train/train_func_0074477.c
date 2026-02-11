dumpTable(Archive *fout, TableInfo *tbinfo)
{
	if (tbinfo->dobj.dump)
	{
		char	   *namecopy;

		if (tbinfo->relkind == RELKIND_SEQUENCE)
			dumpSequence(fout, tbinfo);
		else if (!dataOnly)
			dumpTableSchema(fout, tbinfo);


		namecopy = strdup(fmtId(tbinfo->dobj.name));
		dumpACL(fout, tbinfo->dobj.catId, tbinfo->dobj.dumpId,
				(tbinfo->relkind == RELKIND_SEQUENCE) ? "SEQUENCE" :
				"TABLE",
				namecopy, NULL, tbinfo->dobj.name,
				tbinfo->dobj.namespace->dobj.name, tbinfo->rolname,
				tbinfo->relacl);


		if (g_fout->remoteVersion >= 80400)
		{
			PQExpBuffer query = createPQExpBuffer();
			PGresult   *res;
			int			i;

			appendPQExpBuffer(query,
					   "SELECT attname, attacl FROM pg_catalog.pg_attribute "
							  "WHERE attrelid = '%u' AND NOT attisdropped AND attacl IS NOT NULL "
							  "ORDER BY attnum",
							  tbinfo->dobj.catId.oid);
			res = PQexec(g_conn, query->data);
			check_sql_result(res, g_conn, query->data, PGRES_TUPLES_OK);

			for (i = 0; i < PQntuples(res); i++)
			{
				char	   *attname = PQgetvalue(res, i, 0);
				char	   *attacl = PQgetvalue(res, i, 1);
				char	   *attnamecopy;
				char	   *acltag;

				attnamecopy = strdup(fmtId(attname));
				acltag = malloc(strlen(tbinfo->dobj.name) + strlen(attname) + 2);
				sprintf(acltag, "%s.%s", tbinfo->dobj.name, attname);

				dumpACL(fout, tbinfo->dobj.catId, tbinfo->dobj.dumpId, "TABLE",
						namecopy, attnamecopy, acltag,
						tbinfo->dobj.namespace->dobj.name, tbinfo->rolname,
						attacl);
				free(attnamecopy);
				free(acltag);
			}
			PQclear(res);
			destroyPQExpBuffer(query);
		}

		free(namecopy);
	}
}
