script_variables_read() {
	FILE *f;
	char *line;

	if (!(f = fopen(prepare_path("scripts-var", 0), "r"))) {
		debug("Error opening script variable file..\n");
		return -1;
	}

	while ((line = read_file(f, 0)))
		script_var_add(NULL, NULL, line, NULL, NULL);

	fclose(f);
	return 0;
}
