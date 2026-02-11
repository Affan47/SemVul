PrintQueryStatus(PGresult *results)
{
	char		buf[16];

	if (!pset.quiet)
	{
		if (pset.popt.topt.format == PRINT_HTML)
		{
			fputs("<p>", pset.queryFout);
			html_escaped_print(PQcmdStatus(results), pset.queryFout);
			fputs("</p>\n", pset.queryFout);
		}
		else
			fprintf(pset.queryFout, "%s\n", PQcmdStatus(results));
	}

	if (pset.logfile)
		fprintf(pset.logfile, "%s\n", PQcmdStatus(results));

	snprintf(buf, sizeof(buf), "%u", (unsigned int) PQoidValue(results));
	SetVariable(pset.vars, "LASTOID", buf);
}
