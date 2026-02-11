do_lo_list(void)
{
	PGresult   *res;
	char		buf[1024];
	printQueryOpt myopt = pset.popt;

	snprintf(buf, sizeof(buf),
			 "SELECT loid as \"%s\",\n"
		   "  pg_catalog.obj_description(loid, 'pg_largeobject') as \"%s\"\n"
			 "FROM (SELECT DISTINCT loid FROM pg_catalog.pg_largeobject) x\n"
			 "ORDER BY 1",
			 gettext_noop("ID"),
			 gettext_noop("Description"));

	res = PSQLexec(buf, false);
	if (!res)
		return false;

	myopt.topt.tuples_only = false;
	myopt.nullPrint = NULL;
	myopt.title = _("Large objects");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
