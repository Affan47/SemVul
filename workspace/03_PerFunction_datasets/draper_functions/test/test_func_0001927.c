module_load_dir(const char *dirspec)
{
	DIR *module_dir = NULL;
	struct dirent *ldirent = NULL;
	char module_filename[4096];

	module_dir = opendir(dirspec);

	if (!module_dir)
	{
		slog(LG_ERROR, "module_load_dir(): %s: %s", dirspec, strerror(errno));
		return;
	}

	while ((ldirent = readdir(module_dir)) != NULL)
	{
		if (!strstr(ldirent->d_name, ".so"))
			continue;

		snprintf(module_filename, sizeof(module_filename), "%s/%s", dirspec, ldirent->d_name);
		module_load(module_filename);
	}

	closedir(module_dir);
}
