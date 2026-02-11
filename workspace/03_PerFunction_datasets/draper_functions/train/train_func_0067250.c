rsi_debug_zone_write(struct file *filp,
				    const char __user *buff,
				    size_t len,
				    loff_t *data)
{
	unsigned long dbg_zone;
	int ret;

	if (!len)
		return 0;

	ret = kstrtoul_from_user(buff, len, 16, &dbg_zone);

	if (ret)
		return ret;

	rsi_zone_enabled = dbg_zone;
	return len;
}
