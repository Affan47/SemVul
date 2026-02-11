describeOneTSConfig(const char *oid, const char *nspname, const char *cfgname,
					const char *pnspname, const char *prsname)
{
	PQExpBufferData buf,
				title;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT \n"
					  "  ( SELECT t.alias FROM \n"
					  "    pg_catalog.ts_token_type(c.cfgparser) AS t \n"
					  "    WHERE t.tokid = m.maptokentype ) AS \"%s\", \n"
					  "  pg_catalog.btrim( \n"
				  "    ARRAY( SELECT mm.mapdict::pg_catalog.regdictionary \n"
					  "           FROM pg_catalog.pg_ts_config_map AS mm \n"
					  "           WHERE mm.mapcfg = m.mapcfg AND mm.maptokentype = m.maptokentype \n"
					  "           ORDER BY mapcfg, maptokentype, mapseqno \n"
					  "    ) :: pg_catalog.text , \n"
					  "  '{}') AS \"%s\" \n"
	 "FROM pg_catalog.pg_ts_config AS c, pg_catalog.pg_ts_config_map AS m \n"
					  "WHERE c.oid = '%s' AND m.mapcfg = c.oid \n"
					  "GROUP BY m.mapcfg, m.maptokentype, c.cfgparser \n"
					  "ORDER BY 1;",
					  gettext_noop("Token"),
					  gettext_noop("Dictionaries"),
					  oid);

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	initPQExpBuffer(&title);

	if (nspname)
		appendPQExpBuffer(&title, _("Text search configuration \"%s.%s\""),
						  nspname, cfgname);
	else
		appendPQExpBuffer(&title, _("Text search configuration \"%s\""),
						  cfgname);

	if (pnspname)
		appendPQExpBuffer(&title, _("\nParser: \"%s.%s\""),
						  pnspname, prsname);
	else
		appendPQExpBuffer(&title, _("\nParser: \"%s\""),
						  prsname);

	myopt.nullPrint = NULL;
	myopt.title = title.data;
	myopt.footers = NULL;
	myopt.topt.default_footer = false;
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	termPQExpBuffer(&title);

	PQclear(res);
	return true;
}
