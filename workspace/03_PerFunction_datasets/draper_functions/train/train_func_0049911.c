save_action(bool delete)
{
	FILE *file;
	const char *path;
	char *name;
	const char *line;
	int len;

	path = FILE_cat(FILE_get_dir(COMP_project), ".action", NULL);
	mkdir(path, 0777);
	FILE_set_owner(path, COMP_project);

	name = STR_copy(FILE_set_ext(FILE_get_name(JOB->form), "action"));
	path = FILE_cat(FILE_get_dir(COMP_project), ".action", name, NULL);

	if (delete)
	{
		if (FILE_exist(path))
		{
			if (JOB->verbose)
				printf("Deleting action file %s\n", path);

			FILE_unlink(path);
		}
	}
	else
	{
		if (JOB->verbose)
			printf("Writing action file %s\n", path);

		file = fopen(path, "w");
		if (!file)
			THROW("Cannot create action file: &1", path);

		fputs("# Gambas Action File 3.0\n", file);

		_no_trim = TRUE;
		while (!read_line(&line, &len))
		{
			fwrite(line, sizeof(char), len, file);
			putc('\n', file);
		}
		_no_trim = FALSE;

		if (fclose(file))
			THROW("Cannot create action file: &1", path);

		FILE_set_owner(path, COMP_project);
	}

	STR_free(name);
}
