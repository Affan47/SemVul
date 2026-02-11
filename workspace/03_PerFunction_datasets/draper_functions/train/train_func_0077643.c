handleCopyIn(PGconn *conn, FILE *copystream, bool isbinary)
{
	bool		OK;
	const char *prompt;
	char		buf[COPYBUFSIZ];
	PGresult   *res;


	if (sigsetjmp(sigint_interrupt_jmp, 1) != 0)
	{


		PQputCopyEnd(conn, _("canceled by user"));


		res = PQgetResult(conn);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
			psql_error("%s", PQerrorMessage(conn));
		PQclear(res);

		return false;
	}


	if (isatty(fileno(copystream)))
	{
		if (!pset.quiet)
			puts(_("Enter data to be copied followed by a newline.\n"
				   "End with a backslash and a period on a line by itself."));
		prompt = get_prompt(PROMPT_COPY);
	}
	else
		prompt = NULL;

	OK = true;

	if (isbinary)
	{

		if (prompt)
		{
			fputs(prompt, stdout);
			fflush(stdout);
		}

		for (;;)
		{
			int			buflen;


			sigint_interrupt_enabled = true;

			buflen = fread(buf, 1, COPYBUFSIZ, copystream);

			sigint_interrupt_enabled = false;

			if (buflen <= 0)
				break;

			if (PQputCopyData(conn, buf, buflen) <= 0)
			{
				OK = false;
				break;
			}
		}
	}
	else
	{
		bool		copydone = false;

		while (!copydone)
		{
			bool		firstload;
			bool		linedone;

			if (prompt)
			{
				fputs(prompt, stdout);
				fflush(stdout);
			}

			firstload = true;
			linedone = false;

			while (!linedone)
			{
				int			linelen;
				char	   *fgresult;


				sigint_interrupt_enabled = true;

				fgresult = fgets(buf, sizeof(buf), copystream);

				sigint_interrupt_enabled = false;

				if (!fgresult)
				{
					copydone = true;
					break;
				}

				linelen = strlen(buf);


				if (linelen > 0 && buf[linelen - 1] == '\n')
					linedone = true;


				if (firstload)
				{
					if (strcmp(buf, "\\.\n") == 0 ||
						strcmp(buf, "\\.\r\n") == 0)
					{
						copydone = true;
						break;
					}

					firstload = false;
				}

				if (PQputCopyData(conn, buf, linelen) <= 0)
				{
					OK = false;
					copydone = true;
					break;
				}
			}

			if (copystream == pset.cur_cmd_source)
				pset.lineno++;
		}
	}


	if (ferror(copystream))
		OK = false;


	if (PQputCopyEnd(conn,
					 OK ? NULL : _("aborted because of read failure")) <= 0)
		OK = false;


	res = PQgetResult(conn);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		psql_error("%s", PQerrorMessage(conn));
		OK = false;
	}
	PQclear(res);

	return OK;
}
