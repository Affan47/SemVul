sim_cmd_file(FILE * f, char *s)
{
	char line[4096];
	FILE *cmd_file;
	char *p;

	s++;
	while (isspace(*s))
		s++;

	if (!s || !*s) {
		fprintf(f, "do_cmd_from_file: no file name - skip\n");
		return -1;
	}

	p = s + strlen(s) - 1;
	while (isspace(*p)) {
		*p = '\0';
		p--;
	}

	cmd_file = fopen(s, "r");
	if (!cmd_file) {
		fprintf(f, "do_cmd_from_file: cannot open file \'%s\': %s\n",
			s, strerror(errno));
		return -1;
	}

	while (fgets(line, sizeof(line) - 1, cmd_file) != NULL) {
		do_cmd(line, f);
	}

	fclose(cmd_file);
	return 0;
}
