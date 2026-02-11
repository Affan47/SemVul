listTSParsers(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80300)
	{
		psql_error("The server (version %d.%d) does not support full text search.\n",
				   pset.sversion / 10000, (pset.sversion / 100) % 100);
		return true;
	}

	if (verbose)
		return listTSParsersVerbose(pattern);

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT \n"
					  "  n.nspname as \"%s\",\n"
					  "  p.prsname as \"%s\",\n"
			"  pg_catalog.obj_description(p.oid, 'pg_ts_parser') as \"%s\"\n"
					  "FROM pg_catalog.pg_ts_parser p \n"
		   "LEFT JOIN pg_catalog.pg_namespace n ON n.oid = p.prsnamespace\n",
					  gettext_noop("Schema"),
					  gettext_noop("Name"),
					  gettext_noop("Description")
		);

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  "n.nspname", "p.prsname", NULL,
						  "pg_catalog.pg_ts_parser_is_visible(p.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of text search parsers");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
