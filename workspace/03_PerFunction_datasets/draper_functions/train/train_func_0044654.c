fuse_conn_max_background_write(struct file *file,
					      const char __user *buf,
					      size_t count, loff_t *ppos)
{
	unsigned uninitialized_var(val);
	ssize_t ret;

	ret = fuse_conn_limit_write(file, buf, count, ppos, &val,
				    max_user_bgreq);
	if (ret > 0) {
		struct fuse_conn *fc = fuse_ctl_file_conn_get(file);
		if (fc) {
			fc->max_background = val;
			fuse_conn_put(fc);
		}
	}

	return ret;
}
