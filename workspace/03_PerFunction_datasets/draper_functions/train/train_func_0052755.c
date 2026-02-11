read_bisect_paths(struct argv_array *array)
{
	struct strbuf str = STRBUF_INIT;
	const char *filename = git_path("BISECT_NAMES");
	FILE *fp = fopen(filename, "r");

	if (!fp)
		die_errno("Could not open file '%s'", filename);

	while (strbuf_getline(&str, fp, '\n') != EOF) {
		char *quoted;
		int res;

		strbuf_trim(&str);
		quoted = strbuf_detach(&str, NULL);
		res = sq_dequote_to_argv(quoted, &array->argv,
					 &array->argv_nr, &array->argv_alloc);
		if (res)
			die("Badly quoted content in file '%s': %s",
			    filename, quoted);
	}

	strbuf_release(&str);
	fclose(fp);
}
