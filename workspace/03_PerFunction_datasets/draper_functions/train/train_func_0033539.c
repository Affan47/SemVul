fuse_conn_limit_write(struct file *file, const char __user *buf,
				     size_t count, loff_t *ppos, unsigned *val,
				     unsigned global_limit)
{
	unsigned long t;
	unsigned limit = (1 << 16) - 1;
	int err;

	if (*ppos)
		return -EINVAL;

	err = kstrtoul_from_user(buf, count, 0, &t);
	if (err)
		return err;

	if (!capable(CAP_SYS_ADMIN))
		limit = min(limit, global_limit);

	if (t > limit)
		return -EINVAL;

	*val = t;

	return count;
}
