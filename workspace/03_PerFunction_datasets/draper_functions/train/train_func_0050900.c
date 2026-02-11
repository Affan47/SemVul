traverse(const char *dir, void (*fn)(const char *, struct stat *))
{
	DIR *d;
	struct dirent *de;

	d = opendir(dir);
	if (!d) return;

	while ((de = readdir(d))) {
		char *fname;
		struct stat st;

		if (strcmp(de->d_name,".") == 0) continue;
		if (strcmp(de->d_name,"..") == 0) continue;

		if (strlen(de->d_name) == 0) continue;

		x_asprintf(&fname, "%s/%s", dir, de->d_name);
#ifdef _WIN32
		if (stat(fname, &st))
#else
 		if (lstat(fname, &st))
#endif
                {
			if (errno != ENOENT) {
				perror(fname);
			}
			free(fname);
			continue;
		}

		if (S_ISDIR(st.st_mode)) {
			traverse(fname, fn);
		}

		fn(fname, &st);
		free(fname);
	}

	closedir(d);
}
