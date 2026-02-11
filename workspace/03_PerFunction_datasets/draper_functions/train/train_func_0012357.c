_build_path(char* fname, char **prog_env)
{
	int i;
	char *path_env = NULL, *dir;
	char *file_name, *file_path;
	struct stat stat_buf;
	int len = 256;

	file_name = (char *)xmalloc(len);

	snprintf(file_name, len, "%s", fname);
	for (i=0; i < len; i++) {
		if (file_name[i] == '\0')
			break;
		if (!isspace(file_name[i]))
			continue;
		file_name[i] = '\0';
		break;
	}


	if (file_name[0] == '/')
		return file_name;


	for (i=0; ; i++) {
		if (prog_env[i] == NULL)
			return file_name;
		if (strncmp(prog_env[i], "PATH=", 5))
			continue;
		path_env = xstrdup(&prog_env[i][5]);
		break;
	}

	file_path = (char *)xmalloc(len);
	dir = strtok(path_env, ":");
	while (dir) {
		snprintf(file_path, len, "%s/%s", dir, file_name);
		if (stat(file_path, &stat_buf) == 0)
			break;
		dir = strtok(NULL, ":");
	}
	if (dir == NULL)
		snprintf(file_path, len, "%s", file_name);

	xfree(file_name);
	xfree(path_env);
	return file_path;
}
