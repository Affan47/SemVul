argv_append(const char ***argv, const char *arg)
{
	int argc = 0;

	while (*argv && (*argv)[argc])
		argc++;

	if (!argv_realloc(argv, argc, 2))
		return FALSE;

	(*argv)[argc++] = strdup(arg);
	(*argv)[argc] = NULL;
	return TRUE;
}
