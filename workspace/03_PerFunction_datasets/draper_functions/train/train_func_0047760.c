pg_perm_setlocale(int category, const char *locale)
{
	char	   *result;
	const char *envvar;
	char	   *envbuf;

#ifndef WIN32
	result = setlocale(category, locale);
#else


#ifdef LC_MESSAGES
	if (category == LC_MESSAGES)
	{
		result = (char *) locale;
		if (locale == NULL || locale[0] == '\0')
			return result;
	}
	else
#endif
		result = setlocale(category, locale);
#endif

	if (result == NULL)
		return result;

	switch (category)
	{
		case LC_COLLATE:
			envvar = "LC_COLLATE";
			envbuf = lc_collate_envbuf;
			break;
		case LC_CTYPE:
			envvar = "LC_CTYPE";
			envbuf = lc_ctype_envbuf;
			break;
#ifdef LC_MESSAGES
		case LC_MESSAGES:
			envvar = "LC_MESSAGES";
			envbuf = lc_messages_envbuf;
			break;
#endif
		case LC_MONETARY:
			envvar = "LC_MONETARY";
			envbuf = lc_monetary_envbuf;
			break;
		case LC_NUMERIC:
			envvar = "LC_NUMERIC";
			envbuf = lc_numeric_envbuf;
			break;
		case LC_TIME:
			envvar = "LC_TIME";
			envbuf = lc_time_envbuf;
			break;
		default:
			elog(FATAL, "unrecognized LC category: %d", category);
			envvar = NULL;
			envbuf = NULL;
			break;
	}

	snprintf(envbuf, LC_ENV_BUFSIZE - 1, "%s=%s", envvar, result);

#ifndef WIN32
	if (putenv(envbuf))
		return NULL;
#else


	if (!SetEnvironmentVariable(envvar, result))
		return NULL;
	if (_putenv(envbuf))
		return NULL;
#endif

	return result;
}
