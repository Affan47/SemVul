read_symbols_from_files(const char *filename)
{
	FILE *in = stdin;
	char fname[PATH_MAX];

	if (strcmp(filename, "-") != 0) {
		in = fopen(filename, "r");
		if (!in)
			fatal("Can't open filenames file %s: %m", filename);
	}

	while (fgets(fname, PATH_MAX, in) != NULL) {
		if (strends(fname, "\n"))
			fname[strlen(fname)-1] = '\0';
		read_symbols(fname);
	}

	if (in != stdin)
		fclose(in);
}
