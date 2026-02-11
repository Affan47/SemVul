skip_white_space(const char *query)
{
	int			cnestlevel = 0;

	while (*query)
	{
		int			mblen = PQmblen(query, pset.encoding);


		if (isspace((unsigned char) *query))
			query += mblen;
		else if (query[0] == '/' && query[1] == '*')
		{
			cnestlevel++;
			query += 2;
		}
		else if (cnestlevel > 0 && query[0] == '*' && query[1] == '/')
		{
			cnestlevel--;
			query += 2;
		}
		else if (cnestlevel == 0 && query[0] == '-' && query[1] == '-')
		{
			query += 2;


			while (*query)
			{
				if (*query == '\n')
				{
					query++;
					break;
				}
				query += PQmblen(query, pset.encoding);
			}
		}
		else if (cnestlevel > 0)
			query += mblen;
		else
			break;
	}

	return query;
}
