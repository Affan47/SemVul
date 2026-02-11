vfs_statfs(struct path *path, struct kstatfs *buf)
{
	int error;

	error = statfs_by_dentry(path->dentry, buf);
	if (!error)
		buf->f_flags = calculate_f_flags(path->mnt);
	return error;
}
