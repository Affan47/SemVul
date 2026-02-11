ss_execute_command(sci_idx, argv)
	int sci_idx;
	register char *argv[];
{
	register int i, argc;
	char **argp;

	argc = 0;
	for (argp = argv; *argp; argp++)
		argc++;
	argp = (char **)malloc((argc+1)*sizeof(char *));
	for (i = 0; i <= argc; i++)
		argp[i] = argv[i];
	i = really_execute_command(sci_idx, argc, &argp);
	free(argp);
	return(i);
}
