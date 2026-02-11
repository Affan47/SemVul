describeTablespaces(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80000)
	{
		fprintf(stderr, _("The server (version %d.%d) does not support tablespaces.\n"),
				pset.sversion / 10000, (pset.sversion / 100) % 100);
		return true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT spcname AS \"%s\",\n"
					  "  pg_catalog.pg_get_userbyid(spcowner) AS \"%s\",\n"
					  "  spclocation AS \"%s\"",
					  gettext_noop("Name"),
					  gettext_noop("Owner"),
					  gettext_noop("Location"));

	if (verbose)
	{
		appendPQExpBuffer(&buf, ",\n  ");
		printACLColumn(&buf, "spcacl");
	}

	if (verbose && pset.sversion >= 80200)
		appendPQExpBuffer(&buf,
		 ",\n  pg_catalog.shobj_description(oid, 'pg_tablespace') AS \"%s\"",
						  gettext_noop("Description"));

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
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
