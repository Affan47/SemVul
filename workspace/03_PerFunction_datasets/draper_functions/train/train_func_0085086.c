QCC_CopyString (char *str)
{
	int		old;
	char *s;

	if (opt_noduplicatestrings)
	{
		if (!str || !*str)
			return 0;

		for (s = strings; s < strings+strofs; s++)
			if (!strcmp(s, str))
			{
				optres_noduplicatestrings += strlen(str);
				return s-strings;
			}
	}

	old = strofs;
	strcpy (strings+strofs, str);
	strofs += strlen(str)+1;
	return old;
}
