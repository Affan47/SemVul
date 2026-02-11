adfs_f_free(struct adfs_dir *dir)
{
	int i;

	for (i = dir->nr_buffers - 1; i >= 0; i--) {
		brelse(dir->bh[i]);
		dir->bh[i] = NULL;
	}

	dir->nr_buffers = 0;
	dir->sb = NULL;
}
