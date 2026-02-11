cfs_exists(const char *path)
{
	struct chirp_stat statbuf;
	if(cfs->lstat(path, &statbuf) == 0) {
		return 1;
	} else {
		return 0;
	}
}
