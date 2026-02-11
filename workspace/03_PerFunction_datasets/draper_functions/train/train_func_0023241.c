scandir(const char *path, struct dirent ***namelist,
	    int (*filter) (const struct dirent *),
	    int (*compar)(const struct dirent **,const struct dirent **))

{
	char new_path[4096];

	CHECK_INIT();
	DEBUG("libs_wrap: scandir: %s...\n", path);

	if (is_sysfs_file(path)) {
		convert_sysfs_path(new_path, sizeof(new_path), path);
		path = new_path;
	}

	return real_scandir(path, namelist, filter, compar);
}
