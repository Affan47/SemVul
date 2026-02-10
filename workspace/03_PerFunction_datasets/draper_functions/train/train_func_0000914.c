rsh_file_stat2(file_t* file, int use_lstat)
{
#ifdef _WIN32
	int i;
	(void)use_lstat;

	file->mtime = 0;
	if(file->wpath) {
		free(file->wpath);
		file->wpath = NULL;
	}

	for(i = 0; i < 2; i++) {
		file->wpath = c2w(file->path, i);
		if(file->wpath == NULL) continue;


		if (rsh_file_statw(file) == 0) return 0;

		free(file->wpath);
		file->wpath = NULL;
	}

	if (!errno) errno = EINVAL;
	return -1;
#else
	struct rsh_stat_struct st;
	int res = 0;
	file->mode  = 0;

	do {
		if(use_lstat) {

			if(lstat(file->path, &st) < 0) return -1;
			if(!S_ISLNK(st.st_mode)) break;


			file->mode |= FILE_IFLNK;
		}

		res = rsh_stat(file->path, &st);
	} while(0);

	file->size  = st.st_size;
	file->mtime = st.st_mtime;

	if(S_ISDIR(st.st_mode)) {
		file->mode |= FILE_IFDIR;
	} else if(S_ISREG(st.st_mode)) {

		file->mode |= FILE_IFREG;
	}

	return res;
#endif
}
