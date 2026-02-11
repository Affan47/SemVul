editFile(const char *fname, int lineno)
{
	const char *editorName;
	const char *editor_lineno_arg = NULL;
	char	   *sys;
	int			result;

	Assert(fname != NULL);


	editorName = getenv("PSQL_EDITOR");
	if (!editorName)
		editorName = getenv("EDITOR");
	if (!editorName)
		editorName = getenv("VISUAL");
	if (!editorName)
		editorName = DEFAULT_EDITOR;


	if (lineno > 0)
	{
		editor_lineno_arg = getenv("PSQL_EDITOR_LINENUMBER_ARG");
#ifdef DEFAULT_EDITOR_LINENUMBER_ARG
		if (!editor_lineno_arg)
			editor_lineno_arg = DEFAULT_EDITOR_LINENUMBER_ARG;
#endif
		if (!editor_lineno_arg)
		{
			psql_error("environment variable PSQL_EDITOR_LINENUMBER_ARG must be set to specify a line number\n");
			return false;
		}
	}


#ifndef WIN32
	if (lineno > 0)
		sys = psprintf("exec %s %s%d '%s'",
					   editorName, editor_lineno_arg, lineno, fname);
	else
		sys = psprintf("exec %s '%s'",
					   editorName, fname);
#else
	if (lineno > 0)
		sys = psprintf("\"%s\" %s%d \"%s\"",
					   editorName, editor_lineno_arg, lineno, fname);
	else
		sys = psprintf("\"%s\" \"%s\"",
					   editorName, fname);
#endif
	result = system(sys);
	if (result == -1)
		psql_error("could not start editor \"%s\"\n", editorName);
	else if (result == 127)
		psql_error("could not start /bin/sh\n");
	free(sys);

	return result == 0;
}
