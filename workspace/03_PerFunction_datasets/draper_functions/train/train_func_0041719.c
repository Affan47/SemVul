probes_open(struct inode *inode, struct file *file)
{
	int ret;

	if ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) {
		ret = cleanup_all_probes();
		if (ret)
			return ret;
	}

	return seq_open(file, &probes_seq_op);
}
