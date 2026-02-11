interactive_add(int argc, const char **argv, const char *prefix, int patch)
{
	const char **pathspec = NULL;

	if (argc) {
		pathspec = validate_pathspec(argc, argv, prefix);
		if (!pathspec)
			return -1;
	}

	return run_add_interactive(NULL,
				   patch ? "--patch" : NULL,
				   pathspec);
}
