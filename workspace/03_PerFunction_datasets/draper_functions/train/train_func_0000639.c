__glfs_cwd_set (struct glfs *fs, inode_t *inode)
{
	if (inode->table->xl != fs->active_subvol) {
		inode = __glfs_refresh_inode (fs, fs->active_subvol, inode);
		if (!inode)
			return -1;
	} else {
		inode_ref (inode);
	}

	if (fs->cwd)
		inode_unref (fs->cwd);

	fs->cwd = inode;

	return 0;
}
