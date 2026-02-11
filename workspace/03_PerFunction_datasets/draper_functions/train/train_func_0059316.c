_validate_file(char *path_name, char *gres_name)
{
	char *file_name, *slash, *one_name, *root_path;
	char *formatted_path = NULL;
	hostlist_t hl;
	int i, file_count = 0;

	i = strlen(path_name);
	if ((i < 3) || (path_name[i-1] != ']')) {
		_my_stat(path_name);
		return 1;
	}

	slash = strrchr(path_name, '/');
	if (slash) {
		i = strlen(path_name);
		formatted_path = xmalloc(i+1);
		slash[0] = '\0';
		root_path = xstrdup(path_name);
		xstrcat(root_path, "/");
		slash[0] = '/';
		file_name = slash + 1;
	} else {
		file_name = path_name;
		root_path = NULL;
	}
	hl = hostlist_create(file_name);
	if (hl == NULL)
		fatal("can't parse File=%s", path_name);
	while ((one_name = hostlist_shift(hl))) {
		if (slash) {
			sprintf(formatted_path, "%s/%s", root_path, one_name);
			_my_stat(formatted_path);
		} else {
			_my_stat(one_name);
		}
		file_count++;
		free(one_name);
	}
	hostlist_destroy(hl);
	xfree(formatted_path);
	xfree(root_path);

	return file_count;
}
