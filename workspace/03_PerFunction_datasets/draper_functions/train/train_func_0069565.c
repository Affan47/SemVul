sq_dequote_to_argv(char *arg, const char ***argv, int *nr, int *alloc)
{
	char *next = arg;

	if (!*arg)
		return 0;
	do {
		char *dequoted = sq_dequote_step(next, &next);
		if (!dequoted)
			return -1;
		ALLOC_GROW(*argv, *nr + 1, *alloc);
		(*argv)[(*nr)++] = dequoted;
	} while (next);

	return 0;
}
