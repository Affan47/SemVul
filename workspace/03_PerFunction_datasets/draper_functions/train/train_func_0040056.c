find_origin(void *src_map, struct stat *src_st,
				const char *basepath, const char *subpath)
{
	DIR *dir;
	struct dirent *d;
	char *str, pathname[PATH_MAX];
	struct stat buf;
	int ret;

	if (subpath == NULL)
		strncpy(pathname, basepath, sizeof(pathname));
	else
		snprintf(pathname, sizeof(pathname),
					"%s/%s", basepath, subpath);

	dir = opendir(pathname);
	if (dir == NULL)
		return NULL;

	while ((d = readdir(dir))) {
		if (strcmp(d->d_name, ".") == 0 ||
				strcmp(d->d_name, "..") == 0 ||
				strcmp(d->d_name, "posix") == 0 ||
				strcmp(d->d_name, "right") == 0)
			continue;

		switch (d->d_type) {
		case DT_REG:
			if (subpath == NULL)
				snprintf(pathname, PATH_MAX,
						"%s/%s", basepath, d->d_name);
			else
				snprintf(pathname, PATH_MAX,
						"%s/%s/%s", basepath,
							subpath, d->d_name);

			if (compare_file(src_map, src_st, pathname) == 0) {
				str = g_strdup_printf("%s/%s",
							subpath, d->d_name);
				closedir(dir);
				return str;
			}
			break;
		case DT_UNKNOWN:


			ret = fstatat(dirfd(dir), d->d_name, &buf, 0);
			if (ret < 0)
				continue;
			if ((buf.st_mode & S_IFDIR) == 0)
				continue;

		case DT_DIR:
			if (subpath == NULL)
				strncpy(pathname, d->d_name, sizeof(pathname));
			else
				snprintf(pathname, sizeof(pathname),
						"%s/%s", subpath, d->d_name);

			str = find_origin(src_map, src_st, basepath, pathname);
			if (str != NULL) {
				closedir(dir);
				return str;
			}
			break;
		}
	}

	closedir(dir);

	return NULL;
}
