is_prefix_char (server * serv, char c)
{
	int pos = 0;
	char *np = serv->nick_prefixes;

	while (np[0])
	{
		if (np[0] == c)
			return pos;
		pos++;
		np++;
	}

	if (serv->bad_prefix)
	{
		if (strchr (serv->bad_nick_prefixes, c))

			return -2;
	}

	return -1;
}
