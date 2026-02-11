aufs_poll(struct file *file, poll_table *wait)
{
	unsigned int mask;
	int err;
	struct file *h_file;
	struct super_block *sb;


	mask = POLLERR ;
	sb = file->f_path.dentry->d_sb;
	si_read_lock(sb, AuLock_FLUSH | AuLock_NOPLMW);

	h_file = au_read_pre(file, 0);
	err = PTR_ERR(h_file);
	if (IS_ERR(h_file))
		goto out;


	mask = DEFAULT_POLLMASK;
	if (h_file->f_op->poll)
		mask = h_file->f_op->poll(h_file, wait);
	fput(h_file);

out:
	si_read_unlock(sb);
	AuTraceErr((int)mask);
	return mask;
}
