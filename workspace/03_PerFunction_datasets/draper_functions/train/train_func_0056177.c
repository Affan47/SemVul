load_role(void)
{
	char	   *filename;
	FILE	   *role_file;


	if (role_lines || role_line_nums)
		free_lines(&role_lines, &role_line_nums);
	if (role_sorted)
		pfree(role_sorted);
	role_sorted = NULL;
	role_length = 0;


	filename = auth_getflatfilename();
	role_file = AllocateFile(filename, "r");

	if (role_file == NULL)
	{

		if (errno != ENOENT)
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not open file \"%s\": %m", filename)));
		pfree(filename);
		return;
	}

	tokenize_file(filename, role_file, &role_lines, &role_line_nums);

	FreeFile(role_file);
	pfree(filename);


	role_length = list_length(role_lines);
	if (role_length)
	{
		int			i = 0;
		ListCell   *line;


		role_sorted = palloc(role_length * sizeof(List *));
		foreach(line, role_lines)
			role_sorted[i++] = lfirst(line);
	}
}
