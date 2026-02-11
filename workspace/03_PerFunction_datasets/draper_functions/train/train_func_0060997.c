pstore_file_open(struct inode *inode, struct file *file)
{
	struct pstore_private *ps = inode->i_private;
	struct seq_file *sf;
	int err;
	const struct seq_operations *sops = NULL;

	err = pstore_check_syslog_permissions(ps);
	if (err)
		return err;

	if (ps->type == PSTORE_TYPE_FTRACE)
		sops = &pstore_ftrace_seq_ops;

	err = seq_open(file, sops);
	if (err < 0)
		return err;

	sf = file->private_data;
	sf->private = ps;

	return 0;
}
