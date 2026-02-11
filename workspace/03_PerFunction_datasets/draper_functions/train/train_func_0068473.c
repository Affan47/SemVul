ubifs_update_time(struct inode *inode, struct timespec *time,
			     int flags)
{
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	struct ubifs_budget_req req = { .dirtied_ino = 1,
			.dirtied_ino_d = ALIGN(ui->data_len, 8) };
	int iflags = I_DIRTY_TIME;
	int err, release;

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	mutex_lock(&ui->ui_mutex);
	if (flags & S_ATIME)
		inode->i_atime = *time;
	if (flags & S_CTIME)
		inode->i_ctime = *time;
	if (flags & S_MTIME)
		inode->i_mtime = *time;

	if (!(inode->i_sb->s_flags & MS_LAZYTIME))
		iflags |= I_DIRTY_SYNC;

	release = ui->dirty;
	__mark_inode_dirty(inode, iflags);
	mutex_unlock(&ui->ui_mutex);
	if (release)
		ubifs_release_budget(c, &req);
	return 0;
}
