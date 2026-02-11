getdigestfield(s)
CONST char *s;
{
	CONST char *cp;
	char **argv;
	int quote, argc;

	argv = (char **)Xmalloc(sizeof(*argv));
	argc = 0;

	for (;;) {
		s = skipspace(s);
		if (!*s) break;
		argv = (char **)Xrealloc(argv, (argc + 2) * sizeof(*argv));
		quote = '\0';
		for (cp = s; *cp; cp++) {
			if (*cp == quote) quote = '\0';
			else if (quote) ;
			else if (*cp == '"') quote = *cp;
			else if (*cp == ',') break;
		}
		argv[argc++] = Xstrndup(s, cp - s);
		if (*cp) cp++;
		s = cp;
	}
	argv[argc] = NULL;

	return(argv);
}
