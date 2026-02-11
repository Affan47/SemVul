glfs_h_truncate (struct glfs *fs, struct glfs_object *object, off_t offset)
{
	loc_t               loc = {0, };
	int                 ret = -1;
	xlator_t           *subvol = NULL;
	inode_t            *inode = NULL;


	if ((fs == NULL) || (object == NULL)) {
		errno = EINVAL;
		return -1;
	}

	__glfs_entry_fs (fs);


	subvol = glfs_active_subvol (fs);
	if (!subvol) {
		ret = -1;
		errno = EIO;
		goto out;
	}


	inode = glfs_resolve_inode (fs, subvol, object);
	if (!inode) {
		errno = ESTALE;
		goto out;
	}

	GLFS_LOC_FILL_INODE (inode, loc, out);


	ret = syncop_truncate (subvol, &loc, (off_t)offset);


	if (ret == 0)
		ret = glfs_loc_unlink (&loc);

out:
	loc_wipe (&loc);

	if (inode)
		inode_unref (inode);

	glfs_subvol_done (fs, subvol);

	return ret;
}
