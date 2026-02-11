describeTablespaces(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80000)
	{
		fprintf(stderr, _("The server version (%d) does not support tablespaces.\n"),
				pset.sversion);
		return true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT spcname AS \"%s\",\n"
					  "  pg_catalog.pg_get_userbyid(spcowner) AS \"%s\",\n"
					  "  spclocation AS \"%s\"",
					  _("Name"), _("Owner"), _("Location"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n  spcacl as \"%s\""
		 ",\n  pg_catalog.shobj_description(oid, 'pg_tablespace') AS \"%s\"",
						  _("Access privileges"), _("Description"));

	appendPQExpBuffer(&buf,
					  "\nFROM pg_catalog.pg_tablespace\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL, "spcname", NULL,
						  NULL);

	appendPQExpBuffer(&buf, "ORDER BY 1;");

	res = PSQLexec(buf.data, false);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of tablespaces");

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
