find_matching_ts_config(const char *lc_type)
{
	int			i;
	char	   *langname,
			   *ptr;


	if (lc_type == NULL)
		langname = xstrdup("");
	else
	{
		ptr = langname = xstrdup(lc_type);
		while (*ptr && *ptr != '_' && *ptr != '.' && *ptr != '@')
			ptr++;
		*ptr = '\0';
	}

	for (i = 0; tsearch_config_languages[i].tsconfname; i++)
	{
		if (pg_strcasecmp(tsearch_config_languages[i].langname, langname) == 0)
		{
			free(langname);
			return tsearch_config_languages[i].tsconfname;
		}
	}

	free(langname);
	return NULL;
}
