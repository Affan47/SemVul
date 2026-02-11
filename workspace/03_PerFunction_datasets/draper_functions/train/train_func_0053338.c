delete_dir(const char *dirname)
{
	char subdir[PATH_MAX];
	int result = 0;
	struct dirent *d;
	DIR *dir;

	dir = opendir(dirname);
	if(!dir) {
		if(errno == ENOTDIR)
			return unlink(dirname);
		else if(errno == ENOENT) {


			unlink(dirname);
			return 0;
		}
		else
			return -1;
	}

	while((d = readdir(dir))) {
		if(!strcmp(d->d_name, "."))
			continue;
		if(!strcmp(d->d_name, ".."))
			continue;
		sprintf(subdir, "%s/%s", dirname, d->d_name);
		result = delete_dir(subdir);
	}

	closedir(dir);

	if(rmdir(dirname) != 0) {
		result = -1;
	}

	return result;
}
