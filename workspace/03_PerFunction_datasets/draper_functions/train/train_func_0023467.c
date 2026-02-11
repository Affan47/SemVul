pcipcwd_temp_read(struct file *file, char __user *data,
				size_t len, loff_t *ppos)
{
	int temperature;

	if (pcipcwd_get_temperature(&temperature))
		return -EFAULT;

	if (copy_to_user(data, &temperature, 1))
		return -EFAULT;

	return 1;
}
