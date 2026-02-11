x2sys_get_tracknames (int argc, char **argv, char ***filelist, GMT_LONG *cmdline)
{

	int i, A, list = 0, add_chunk, n_alloc;
	char **file = NULL, *p = NULL;


	for (A = 1; !list && A < argc; A++) if (argv[A][0] == ':' || argv[A][0] == '=') list = A;

	if (list) {
		*cmdline = FALSE;
		if (x2sys_read_list (&argv[list][1], filelist, &A) != X2SYS_NOERROR) {
			fprintf (stderr, "%s: Error: Could not open list with filenames %s!\n", GMT_program, &argv[list][1]);
			exit (EXIT_FAILURE);
		}
		file = *filelist;
	}
	else {
		add_chunk = n_alloc = GMT_CHUNK;
		file = (char **)GMT_memory (VNULL, (size_t)n_alloc, sizeof (char *), GMT_program);

		*cmdline = TRUE;
		for (i = 1, A = 0; i < argc; i++) {
			if (argv[i][0] == '-') continue;

			file[A++] = strdup (argv[i]);
			if (A == n_alloc) {
				add_chunk <<= 1;
				n_alloc += add_chunk;
				file = (char **)GMT_memory ((void *)file, (size_t)n_alloc, sizeof (char *), GMT_program);
			}
		}
		file = (char **)GMT_memory ((void *)file, (size_t)A, sizeof (char *), GMT_program);
		*filelist = file;
	}


	for (i = 0; i < A; i++) {
		if ((p = strchr (file[i], '.'))) file[i][(int)(p-file[i])] = '\0';
	}

	return (A);
}
