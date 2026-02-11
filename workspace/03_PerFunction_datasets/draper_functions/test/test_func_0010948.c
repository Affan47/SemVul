glfs_stat (struct glfs *fs, const char *path, struct stat *stat)
{
	int              ret = -1;
	xlator_t        *subvol = NULL;
	loc_t            loc = {0, };
	struct iatt      iatt = {0, };
	int              reval = 0;

	__glfs_entry_fs (fs);

	subvol = glfs_active_subvol (fs);
	if (!subvol) {
		ret = -1;
		errno = EIO;
		goto out;
	}
retry:
	ret = glfs_resolve (fs, subvol, path, &loc, &iatt, reval);

	ESTALE_RETRY (ret, errno, reval, &loc, retry);

	if (ret == 0 && stat)
		glfs_iatt_to_stat (fs, &iatt, stat);
out:
	loc_wipe (&loc);

	glfs_subvol_done (fs, subvol);

	return ret;
}
