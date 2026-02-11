InitMsyms()

{
	auto int	rtn,
			tmp;

	FILE *ksyms;

	char buf[128];
	char *p;


	FreeModules();

	ksyms = fopen(KSYMS, "r");

	if ( ksyms == NULL )
	{
		if ( errno == ENOENT )
			Syslog(LOG_INFO, "No module symbols loaded - "
			       "kernel modules not enabled.\n");
		else
			Syslog(LOG_ERR, "Error loading kernel symbols " \
			       "- %s\n", strerror(errno));
		fclose(ksyms);
		return(0);
	}

	if ( debugging )
		fprintf(stderr, "Loading kernel module symbols - "
			"Source: %s\n", KSYMS);

	while ( fgets(buf, sizeof(buf), ksyms) != NULL )
	{
		if (num_syms > 0 && index(buf, '[') == NULL)
			continue;

		p = index(buf, ' ');

		if ( p == NULL )
			continue;

		if ( buf[strlen(buf)-1] == '\n' )
			buf[strlen(buf)-1] = '\0';


		AddSymbol(buf);
	}

	fclose(ksyms);

	have_modules = 1;


	for (rtn = tmp = 0; tmp < num_modules; ++tmp)
	{
		rtn += sym_array_modules[tmp].num_syms;
		if ( sym_array_modules[tmp].num_syms < 2 )
			continue;
		qsort(sym_array_modules[tmp].sym_array, \
		      sym_array_modules[tmp].num_syms, \
		      sizeof(struct sym_table), symsort);
	}

	if ( rtn == 0 )
		Syslog(LOG_INFO, "No module symbols loaded.");
	else
		Syslog(LOG_INFO, "Loaded %d %s from %d module%s", rtn, \
		       (rtn == 1) ? "symbol" : "symbols", \
		       num_modules, (num_modules == 1) ? "." : "s.");

	return(1);
}
