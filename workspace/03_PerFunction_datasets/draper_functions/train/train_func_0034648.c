gpio_power_write(struct file *file,
			   const char __user *user_buf,
			   size_t count, loff_t *ppos)
{
	struct wl1271 *wl = file->private_data;
	unsigned long value;
	int ret;

	ret = kstrtoul_from_user(user_buf, count, 10, &value);
	if (ret < 0) {
		wl1271_warning("illegal value in gpio_power");
		return -EINVAL;
	}

	mutex_lock(&wl->mutex);

	if (value)
		wl1271_power_on(wl);
	else
		wl1271_power_off(wl);

	mutex_unlock(&wl->mutex);
	return count;
}
