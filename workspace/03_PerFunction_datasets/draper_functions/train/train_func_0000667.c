restore(const char *filename)
{
	static char *path;
	static size_t path_size;
	FILE *file;
	char *l;
	int line = 0, backup_line, status = 0;

	if (strcmp(filename, "-") == 0)
		file = stdin;
	else {
		file = fopen(filename, "r");
		if (file == NULL) {
				fprintf(stderr, "%s: %s: %s\n",
					progname, filename, strerror_ea(errno));
				return 1;
		}
	}

	for(;;) {
		backup_line = line;
		while ((l = next_line(file)) != NULL && *l == '\0')
			line++;
		if (l == NULL)
			break;
		line++;
		if (strncmp(l, "# file: ", 8) != 0) {
			if (file != stdin) {
				fprintf(stderr, _("%s: %s: No filename found "
				                  "in line %d, aborting\n"),
					progname, filename, backup_line);
			} else {
				fprintf(stderr, _("%s: No filename found in "
			                          "line %d of standard input, "
						  "aborting\n"),
					  progname, backup_line);
			}
			status = 1;
			goto cleanup;
		} else
			l += 8;
		l = unquote(l);
		if (high_water_alloc((void **)&path, &path_size, strlen(l)+1)) {
			perror(progname);
			status = 1;
			goto cleanup;
		}
		strcpy(path, l);

		while ((l = next_line(file)) != NULL && *l != '\0') {
			char *name = l, *value = strchr(l, '=');
			line++;
			if (value)
				*value++ = '\0';
			status = do_set(path, unquote(name), value);
		}
		if (l == NULL)
			break;
		line++;
	}
	if (!feof(file)) {
		fprintf(stderr, "%s: %s: %s\n", progname, filename,
			strerror(errno));
		if (!status)
			status = 1;
	}

cleanup:
	if (path)
		free(path);
	if (file != stdin)
		fclose(file);
	if (status)
		had_errors++;
	return status;
}
