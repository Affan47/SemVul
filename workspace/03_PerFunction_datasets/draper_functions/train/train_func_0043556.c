usnic_debugfs_buildinfo_read(struct file *f, char __user *data,
						size_t count, loff_t *ppos)
{
	char buf[500];
	int res;

	if (*ppos > 0)
		return 0;

	res = scnprintf(buf, sizeof(buf),
			"version:       %s\n"
			"build date:    %s\n",
			DRV_VERSION, DRV_RELDATE);

	return simple_read_from_buffer(data, count, ppos, buf, res);
}
