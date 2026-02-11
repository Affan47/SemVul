get_progname(const char *argv0)
{
	const char *nodir_name;
	char *progname;

	nodir_name = last_dir_separator(argv0);
	if (nodir_name)
		nodir_name++;
	else
		nodir_name = skip_drive(argv0);


	progname = strdup(nodir_name);
	if (progname == NULL) {
		fprintf(stderr, "%s: out of memory\n", nodir_name);
		exit(1);
	}

#if defined(__CYGWIN__) || defined(WIN32)

	if (strlen(progname) > sizeof(EXE) - 1
		&& pg_strcasecmp(progname + strlen(progname) - (sizeof(EXE) - 1), EXE) == 0)
		progname[strlen(progname) - (sizeof(EXE) - 1)] = '\0';
#endif

	return progname;
}
