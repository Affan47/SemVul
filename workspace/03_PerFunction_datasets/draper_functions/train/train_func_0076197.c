add_local_domain(char *hname, size_t size)
{

	if (strchr(hname, '.') == NULL)
	{
		if (irc_domain[0])
		{
			size_t len = strlen(hname);

			if ((strlen(irc_domain) + len + 2) < size)
			{
				hname[len++] = '.';
				strcpy(hname + len, irc_domain);
			}
		}
	}
}
