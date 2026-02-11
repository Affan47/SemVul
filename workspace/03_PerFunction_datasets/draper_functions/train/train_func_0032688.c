history_read() {
	FILE *f_in = NULL;
	char *filename = NULL;
	GList *history = NULL;
	char line[4096];

	filename = (char *)malloc(sizeof(char) * (strlen(getenv("HOME")) + 15 + 1) );
	sprintf(filename, "%s/.gexec_history", getenv("HOME"));

	f_in = fopen(filename, "r");
	if (f_in != NULL) {

		while (fgets(line, 4096, f_in)) {
			char *newline_pos;

			newline_pos = strchr(line, '\n');
			newline_pos[0] = '\0';

			history = g_list_append(history, strdup(line));
		}

		fclose(f_in);
	}

	free(filename);

	return(history);
}
