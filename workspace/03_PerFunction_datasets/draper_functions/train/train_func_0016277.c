chirp_fs_local_rmdir(const char *path)
{
	struct chirp_dir *dir;
	struct chirp_dirent *d;
	int empty = 1;

	dir = chirp_fs_local_opendir(path);
	if(dir) {
		while((d = chirp_fs_local_readdir(dir))) {
			if(!strcmp(d->name, "."))
				continue;
			if(!strcmp(d->name, ".."))
				continue;
			if(!strncmp(d->name, ".__", 3))
				continue;
			empty = 0;
			break;
		}
		chirp_fs_local_closedir(dir);

		if(empty) {
			return delete_dir(path);
		} else {
			errno = ENOTEMPTY;
			return -1;
		}
	} else {
		return -1;
	}
}
