permissionsList(const char *pattern)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, true, false, false, false};

	initPQExpBuffer(&buf);


	printfPQExpBuffer(&buf,
					  "SELECT n.nspname as \"%s\",\n"
					  "  c.relname as \"%s\",\n"
					  "  CASE c.relkind"
					  " WHEN 'r' THEN '%s'"
					  " WHEN 'v' THEN '%s'"
					  " WHEN 'm' THEN '%s'"
					  " WHEN 'S' THEN '%s'"
					  " WHEN 'f' THEN '%s'"
					  " END as \"%s\",\n"
					  "  ",
					  gettext_noop("Schema"),
					  gettext_noop("Name"),
					  gettext_noop("table"),
					  gettext_noop("view"),
					  gettext_noop("materialized view"),
					  gettext_noop("sequence"),
					  gettext_noop("foreign table"),
					  gettext_noop("Type"));

	printACLColumn(&buf, "c.relacl");

	if (pset.sversion >= 80400)
		appendPQExpBuffer(&buf,
						  ",\n  pg_catalog.array_to_string(ARRAY(\n"
						  "    SELECT attname || E':\\n  ' || pg_catalog.array_to_string(attacl, E'\\n  ')\n"
						  "    FROM pg_catalog.pg_attribute a\n"
						  "    WHERE attrelid = c.oid AND NOT attisdropped AND attacl IS NOT NULL\n"
						  "  ), E'\\n') AS \"%s\"",
						  gettext_noop("Column privileges"));

	if (pset.sversion >= 90500)
		appendPQExpBuffer(&buf,
						  ",\n  pg_catalog.array_to_string(ARRAY(\n"
						  "    SELECT polname\n"
						  "    || CASE WHEN polcmd != '*' THEN\n"
						  "           E' (' || polcmd || E'):'\n"
						  "       ELSE E':' \n"
						  "       END\n"
						  "    || CASE WHEN polqual IS NOT NULL THEN\n"
						  "           E'\\n  (u): ' || pg_catalog.pg_get_expr(polqual, polrelid)\n"
						  "       ELSE E''\n"
						  "       END\n"
						  "    || CASE WHEN polwithcheck IS NOT NULL THEN\n"
						  "           E'\\n  (c): ' || pg_catalog.pg_get_expr(polwithcheck, polrelid)\n"
						  "       ELSE E''\n"
						  "       END"
						  "    || CASE WHEN polroles <> '{0}' THEN\n"
				   "           E'\\n  to: ' || pg_catalog.array_to_string(\n"
						  "               ARRAY(\n"
						  "                   SELECT rolname\n"
						  "                   FROM pg_catalog.pg_roles\n"
						  "                   WHERE oid = ANY (polroles)\n"
						  "                   ORDER BY 1\n"
						  "               ), E', ')\n"
						  "       ELSE E''\n"
						  "       END\n"
						  "    FROM pg_catalog.pg_policy pol\n"
						  "    WHERE polrelid = c.oid), E'\\n')\n"
						  "    AS \"%s\"",
						  gettext_noop("Policies"));

	appendPQExpBufferStr(&buf, "\nFROM pg_catalog.pg_class c\n"
	   "     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace\n"
						 "WHERE c.relkind IN ('r', 'v', 'm', 'S', 'f')\n");


	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "c.relname", NULL,
			"n.nspname !~ '^pg_' AND pg_catalog.pg_table_is_visible(c.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	if (!res)
	{
		termPQExpBuffer(&buf);
		return false;
	}

	myopt.nullPrint = NULL;
	printfPQExpBuffer(&buf, _("Access privileges"));
	myopt.title = buf.data;
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	termPQExpBuffer(&buf);
	PQclear(res);
	return true;
}
