write_file_spectral_count(struct file *file,
					 const char __user *user_buf,
					 size_t count, loff_t *ppos)
{
	struct ath10k *ar = file->private_data;
	unsigned long val;
	char buf[32];
	ssize_t len;

	len = min(count, sizeof(buf) - 1);
	if (copy_from_user(buf, user_buf, len))
		return -EFAULT;

	buf[len] = '\0';
	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	if (val < 0 || val > 255)
		return -EINVAL;

	mutex_lock(&ar->conf_mutex);
	ar->spectral.config.count = val;
	mutex_unlock(&ar->conf_mutex);

	return count;
}
