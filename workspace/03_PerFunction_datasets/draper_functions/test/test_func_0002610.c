create_directories(char* path) {
	char* lastslash = strrchr(path, '/');
	if (lastslash == NULL)
		return 0;

	*lastslash = '\0';

	int ret = mkdir(path, 0777);
	if (ret == -1 && errno == ENOENT) {
		if ((ret = create_directories(path)) == 0)
			ret = mkdir(path, 0777);
	}

	*lastslash = '/';

	if (ret == -1 && errno == EEXIST)
		ret = 0;

	return ret;
}
