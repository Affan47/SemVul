read_cvsrc (int *argc, char ***argv, const char *cmdname)
{
    char *homedir;
    char *homeinit;
    FILE *cvsrcfile;

    char *line;
    int line_length;
    size_t line_chars_allocated;

    char *optstart;
    int white_len = 0;

    int command_len;
    int found = 0;

    int i;

    int new_argc;
    int max_new_argv;
    char **new_argv;


    static int old_argc = 0;
    static char **old_argv = NULL;


    if (*argc == -1)
	return;


    homedir = get_homedir ();


    if (!homedir)
	return;

    homeinit = strcat_filename_onto_homedir (homedir, cvsrc);


    if (!isreadable (homeinit))
    {
	free (homeinit);
	return;
    }


    line = NULL;
    line_chars_allocated = 0;
    command_len = strlen (cmdname);
    cvsrcfile = xfopen (homeinit, "r");
    while ((line_length = getline (&line, &line_chars_allocated, cvsrcfile))
	   >= 0)
    {

	if (line[0] == '#')
	    continue;

	while (isspace(line[white_len]))
		++white_len;


	if (!strncmp (line + white_len, cmdname, command_len)
	    && isspace ((unsigned char) *(line + white_len + command_len)))
	{
	    found = 1;
	    break;
	}
    }

    if (line_length < 0 && !feof (cvsrcfile))
	error (0, errno, "cannot read %s", homeinit);

    fclose (cvsrcfile);


    new_argc = 1;
    max_new_argv = (*argc) + GROW;
    new_argv = xnmalloc (max_new_argv, sizeof (char *));
    new_argv[0] = xstrdup ((*argv)[0]);

    if (found)
    {

	for (optstart = strtok (line + white_len + command_len, "\t \n");
	     optstart;
	     optstart = strtok (NULL, "\t \n"))
	{
	    new_argv [new_argc++] = xstrdup (optstart);

	    if (new_argc >= max_new_argv)
	    {
		max_new_argv += GROW;
		new_argv = xnrealloc (new_argv, max_new_argv, sizeof (char *));
	    }
	}
    }

    if (line != NULL)
	free (line);


    if (new_argc + *argc > max_new_argv)
    {
	max_new_argv = new_argc + *argc;
	new_argv = xnrealloc (new_argv, max_new_argv, sizeof (char *));
    }
    for (i = 1; i < *argc; i++)
	new_argv [new_argc++] = xstrdup ((*argv)[i]);

    if (old_argv != NULL)
    {


	free_names (&old_argc, old_argv);
    }

    old_argc = *argc = new_argc;
    old_argv = *argv = new_argv;

    free (homeinit);
    return;
}
