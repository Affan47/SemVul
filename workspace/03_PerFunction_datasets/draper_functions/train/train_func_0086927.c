regex_create(char *pattern, int flags)
{
	static char errmsg[BUFSIZE];
	int errnum;
	atheme_regex_t *preg;

	if (pattern == NULL)
	{
		return NULL;
	}

	preg = smalloc(sizeof(atheme_regex_t));
	if (flags & AREGEX_PCRE)
	{
#ifdef HAVE_PCRE
		const char *errptr;
		int erroffset;

		preg->un.pcre = pcre_compile(pattern, (flags & AREGEX_ICASE ? PCRE_CASELESS : 0) | PCRE_NO_AUTO_CAPTURE, &errptr, &erroffset, NULL);
		if (preg->un.pcre == NULL)
		{
			slog(LG_ERROR, "regex_match(): %s at offset %d in %s",
					errptr, erroffset, pattern);
			free(preg);
			return NULL;
		}
		preg->type = at_pcre;
#else
		slog(LG_ERROR, "regex_match(): PCRE support is not compiled in");
		free(preg);
		return NULL;
#endif
	}
	else
	{
		errnum = regcomp(&preg->un.posix, pattern, (flags & AREGEX_ICASE ? REG_ICASE : 0) | REG_EXTENDED);

		if (errnum != 0)
		{
			regerror(errnum, &preg->un.posix, errmsg, BUFSIZE);
			slog(LG_ERROR, "regex_match(): %s in %s",
					errmsg, pattern);
			regfree(&preg->un.posix);
			free(preg);
			return NULL;
		}
		preg->type = at_posix;
	}

	return preg;
}
