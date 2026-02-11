watchdog_write(struct file *file, const char __user *data,
						size_t len, loff_t *ppos)
{
	struct watchdog_device *wdd = file->private_data;
	size_t i;
	char c;
	int err;

	if (len == 0)
		return 0;


	clear_bit(WDOG_ALLOW_RELEASE, &wdd->status);


	for (i = 0; i != len; i++) {
		if (get_user(c, data + i))
			return -EFAULT;
		if (c == 'V')
			set_bit(WDOG_ALLOW_RELEASE, &wdd->status);
	}


	err = watchdog_ping(wdd);
	if (err < 0)
		return err;

	return len;
}
