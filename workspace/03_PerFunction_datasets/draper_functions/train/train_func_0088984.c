describeFunctions(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT n.nspname as \"%s\",\n"
					  "  p.proname as \"%s\",\n"
					  "  CASE WHEN p.proretset THEN 'setof ' ELSE '' END ||\n"
				  "  pg_catalog.format_type(p.prorettype, NULL) as \"%s\",\n"
					  "  CASE WHEN proallargtypes IS NOT NULL THEN\n"
					  "    pg_catalog.array_to_string(ARRAY(\n"
					  "      SELECT\n"
					  "        CASE\n"
					  "          WHEN p.proargmodes[s.i] = 'i' THEN ''\n"
					  "          WHEN p.proargmodes[s.i] = 'o' THEN 'OUT '\n"
					"          WHEN p.proargmodes[s.i] = 'b' THEN 'INOUT '\n"
					  "        END ||\n"
					  "        CASE\n"
			 "          WHEN COALESCE(p.proargnames[s.i], '') = '' THEN ''\n"
					  "          ELSE p.proargnames[s.i] || ' ' \n"
					  "        END ||\n"
			  "        pg_catalog.format_type(p.proallargtypes[s.i], NULL)\n"
					  "      FROM\n"
					  "        pg_catalog.generate_series(1, pg_catalog.array_upper(p.proallargtypes, 1)) AS s(i)\n"
					  "    ), ', ')\n"
					  "  ELSE\n"
					  "    pg_catalog.array_to_string(ARRAY(\n"
					  "      SELECT\n"
					  "        CASE\n"
		   "          WHEN COALESCE(p.proargnames[s.i+1], '') = '' THEN ''\n"
					  "          ELSE p.proargnames[s.i+1] || ' '\n"
					  "          END ||\n"
				 "        pg_catalog.format_type(p.proargtypes[s.i], NULL)\n"
					  "      FROM\n"
					  "        pg_catalog.generate_series(0, pg_catalog.array_upper(p.proargtypes, 1)) AS s(i)\n"
					  "    ), ', ')\n"
					  "  END AS \"%s\"",
					  _("Schema"), _("Name"), _("Result data type"),
					  _("Argument data types"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n  r.rolname as \"%s\",\n"
						  "  l.lanname as \"%s\",\n"
						  "  p.prosrc as \"%s\",\n"
				  "  pg_catalog.obj_description(p.oid, 'pg_proc') as \"%s\"",
						  _("Owner"), _("Language"),
						  _("Source code"), _("Description"));

	if (!verbose)
		appendPQExpBuffer(&buf,
						  "\nFROM pg_catalog.pg_proc p"
						  "\n     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = p.pronamespace\n");
	else
		appendPQExpBuffer(&buf,
						  "\nFROM pg_catalog.pg_proc p"
		"\n     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = p.pronamespace"
			 "\n     LEFT JOIN pg_catalog.pg_language l ON l.oid = p.prolang"
				"\n     JOIN pg_catalog.pg_roles r ON r.oid = p.proowner\n");


	appendPQExpBuffer(&buf,
		   "WHERE p.prorettype <> 'pg_catalog.cstring'::pg_catalog.regtype\n"
					  "      AND (p.proargtypes[0] IS NULL\n"
					  "      OR   p.proargtypes[0] <> 'pg_catalog.cstring'::pg_catalog.regtype)\n"
					  "      AND NOT p.proisagg\n");

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "p.proname", NULL,
						  "pg_catalog.pg_function_is_visible(p.oid)");

	appendPQExpBuffer(&buf, "ORDER BY 1, 2, 3, 4;");

	res = PSQLexec(buf.data, false);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of functions");

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
