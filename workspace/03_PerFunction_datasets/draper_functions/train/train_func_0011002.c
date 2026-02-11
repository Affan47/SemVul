next_token(FILE *fp, char *buf, int bufsz, bool *initial_quote)
{
	int			c;
	char	   *start_buf = buf;
	char	   *end_buf = buf + (bufsz - 2);
	bool		in_quote = false;
	bool		was_quote = false;
	bool		saw_quote = false;


	Assert(end_buf > start_buf);

	*initial_quote = false;


	while ((c = getc(fp)) != EOF && (pg_isblank(c) || c == ','))
		;

	if (c == EOF || c == '\n')
	{
		*buf = '\0';
		return false;
	}


	while (c != EOF && c != '\n' &&
		   (!pg_isblank(c) || in_quote))
	{

		if (c == '#' && !in_quote)
		{
			while ((c = getc(fp)) != EOF && c != '\n')
				;

			if (c != EOF && buf == start_buf)
				c = getc(fp);
			break;
		}

		if (buf >= end_buf)
		{
			*buf = '\0';
			ereport(LOG,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
			   errmsg("authentication file token too long, skipping: \"%s\"",
					  start_buf)));

			while ((c = getc(fp)) != EOF && c != '\n')
				;
			break;
		}

		if (c != '"' || was_quote)
			*buf++ = c;


		if (c == ',' && !in_quote)
			break;


		if (in_quote && c == '"')
			was_quote = !was_quote;
		else
			was_quote = false;

		if (c == '"')
		{
			in_quote = !in_quote;
			saw_quote = true;
			if (buf == start_buf)
				*initial_quote = true;
		}

		c = getc(fp);
	}


	if (c != EOF)
		ungetc(c, fp);

	*buf = '\0';

	if (!saw_quote &&
		(strcmp(start_buf, "all") == 0 ||
		 strcmp(start_buf, "samehost") == 0 ||
		 strcmp(start_buf, "samenet") == 0 ||
		 strcmp(start_buf, "sameuser") == 0 ||
		 strcmp(start_buf, "samegroup") == 0 ||
		 strcmp(start_buf, "samerole") == 0 ||
		 strcmp(start_buf, "replication") == 0))
	{

		*buf++ = '\n';
		*buf = '\0';
	}

	return (saw_quote || buf > start_buf);
}
