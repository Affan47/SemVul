tracing_stat_open(struct inode *inode, struct file *file)
{
	int ret;
	struct seq_file *m;
	struct stat_session *session = inode->i_private;

	ret = stat_seq_init(session);
	if (ret)
		return ret;

	ret = seq_open(file, &trace_stat_seq_ops);
	if (ret) {
		reset_stat_session(session);
		return ret;
	}

	m = file->private_data;
	m->private = session;
	return ret;
}
