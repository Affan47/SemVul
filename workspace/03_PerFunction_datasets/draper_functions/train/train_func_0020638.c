glusterfs_oldvolfile_update (struct glfs *fs, char *volfile, ssize_t size)
{
	int ret = -1;

	fs->oldvollen = size;
	if (!fs->oldvolfile) {
		fs->oldvolfile = GF_CALLOC (1, size+1, glfs_mt_volfile_t);
	} else {
		fs->oldvolfile = GF_REALLOC (fs->oldvolfile, size+1);
	}

	if (!fs->oldvolfile) {
		fs->oldvollen = 0;
	} else {
		memcpy (fs->oldvolfile, volfile, size);
		fs->oldvollen = size;
		ret = 0;
	}

	return ret;
}
