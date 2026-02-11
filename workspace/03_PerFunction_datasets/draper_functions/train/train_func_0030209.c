do_track(struct trackspec *tr)
{
	struct converter *converter;
	char *c2t_from_prefix = "C2T_FROM=";
	char *c2t_to_prefix   = "C2T_TO=";
	char *c2t_from;
	char *c2t_to;
	char *c2t_to_filename;
	struct stat statbuf;
	int status;

	if ((converter = find_converter(tr->filename)) == NULL)
		return;

	if (debug) fprintf(stderr, "Found a converter for track %d: %s\n",
			   trackno, converter->command);

	if ((c2t_from = malloc(strlen(c2t_from_prefix)
			       + strlen(tr->filename) + 1)) == NULL)
		err_quit("Memory allocation error");
	if ((c2t_to = malloc(strlen(c2t_to_prefix) + strlen(tr->filename)
			     - strlen(converter->ext_from)
			     + strlen(converter->ext_to) + 1)) == NULL)
		err_quit("Memory allocation error");
	if ((c2t_to_filename = malloc(strlen(tr->filename)
			     - strlen(converter->ext_from)
			     + strlen(converter->ext_to) + 1)) == NULL)
		err_quit("Memory allocation error");


	strcpy(c2t_from, c2t_from_prefix);
	strcat(c2t_from, tr->filename);


	strcpy(c2t_to, c2t_to_prefix);
	strncat(c2t_to, tr->filename,
		strlen(tr->filename) - strlen(converter->ext_from));
	strcat(c2t_to, converter->ext_to);


	strncpy(c2t_to_filename, tr->filename, strlen(tr->filename)
					       - strlen(converter->ext_from));
	c2t_to_filename[strlen(tr->filename)
			- strlen(converter->ext_from)] = '\0';
	strcat(c2t_to_filename, converter->ext_to);

	if (stat(c2t_to_filename, &statbuf) != -1) {
		if (debug) fprintf(stderr, "%s already exists\n",
				   c2t_to_filename);
		free(c2t_from);
		free(c2t_to);
		strcpy(tr->filename, c2t_to_filename);
		free(c2t_to_filename);

		return;
	}

	if (debug) fprintf(stderr, "Exporting \"%s\"\n", c2t_from);
	if (putenv(c2t_from) == -1)
		err_sys("putenv error");

	if (debug) fprintf(stderr, "Exporting \"%s\"\n", c2t_to);
	if (putenv(c2t_to) == -1)
		err_sys("putenv error");


	if (!quiet)
		fprintf(stderr, "%s: Track %d: Converting \"%s\" to \"%s\"\n",
			prog, trackno, tr->filename, c2t_to_filename);

	if ((status = system(converter->command)) == -1)
		err_sys("system error");

	if (debug) fprintf(stderr, "Conversion command returned with "
			   "exit status %d\n", WEXITSTATUS(status));


	strcpy(tr->filename, c2t_to_filename);


	free(c2t_to_filename);
}
