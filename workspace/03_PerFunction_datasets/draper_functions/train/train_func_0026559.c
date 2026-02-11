showconf(void)
{
#if defined(CONFIG_DIRECTIVE_INCLUDE)
	aConfig *p, *p2;
	int etclen = 0;
	FILE *fdn;
#else
	int dh;
	char	line[512], c[80], *tmp;
#endif
	int fd;

	fprintf(stderr, "showconf(): %s\n", configfile);
	if ((fd = openconf()) == -1)
	    {
#ifdef	M4_PREPROC
		(void)wait(0);
#endif
		return;
	    }
#if defined(CONFIG_DIRECTIVE_INCLUDE)
	if (debugflag)
	{
		etclen = strlen(IRCDCONF_DIR);
	}
	fdn = fdopen(fd, "r");
	p2 = config_read(fdn, 0, new_config_file(configfile, NULL, 0));
	for(p = p2; p; p = p->next)
	{
		if (debugflag)
			printf("%s:%d:", p->file->filename +
				(strncmp(p->file->filename, IRCDCONF_DIR,
				etclen) == 0 ? etclen : 0), p->linenum);
		printf("%s\n", p->line);
	}
	config_free(p2);
	(void)fclose(fdn);
#else
	(void)dgets(-1, NULL, 0);
	while ((dh = dgets(fd, line, sizeof(line) - 1)) > 0)
	{
		if ((tmp = (char *)index(line, '\n')))
			*tmp = 0;
		else while(dgets(fd, c, sizeof(c) - 1))
			if ((tmp = (char *)index(c, '\n')))
			{
				*tmp = 0;
				break;
			}
		printf("%s\n", line);
	}
	(void)close(fd);
#endif
#ifdef	M4_PREPROC
	(void)wait(0);
#endif
	return;
}
