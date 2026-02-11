is_dir(char * path) {

	struct stat st_file;

	if (stat(path, &st_file) == -1) {
		return 0;
	}

	return S_ISDIR(st_file.st_mode);
}
