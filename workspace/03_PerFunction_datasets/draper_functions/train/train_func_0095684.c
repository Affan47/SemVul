picolcd_debug_flash_write(struct file *f, const char __user *u,
		size_t s, loff_t *off)
{
	struct picolcd_data *data = f->private_data;
	ssize_t err, ret = 0;
	int report_erase, report_write;

	if (s == 0)
		return -EINVAL;
	if (*off > 0x5fff)
		return -ENOSPC;
	if (s & 0x3f)
		return -EINVAL;
	if (*off & 0x3f)
		return -EINVAL;

	if (data->status & PICOLCD_BOOTLOADER) {
		report_erase = REPORT_BL_ERASE_MEMORY;
		report_write = REPORT_BL_WRITE_MEMORY;
	} else {
		report_erase = REPORT_ERASE_MEMORY;
		report_write = REPORT_WRITE_MEMORY;
	}
	mutex_lock(&data->mutex_flash);
	while (s > 0) {
		err = _picolcd_flash_erase64(data, report_erase, off);
		if (err)
			break;
		err = _picolcd_flash_write(data, report_write, u, 64, off);
		if (err < 0)
			break;
		ret += err;
		*off += err;
		s -= err;
		if (err != 64)
			break;
	}
	mutex_unlock(&data->mutex_flash);
	return ret > 0 ? ret : err;
}
