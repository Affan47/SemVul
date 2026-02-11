event_filter_write(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct trace_event_file *file;
	char *buf;
	int err = -ENODEV;

	if (cnt >= PAGE_SIZE)
		return -EINVAL;

	buf = (char *)__get_free_page(GFP_TEMPORARY);
	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, ubuf, cnt)) {
		free_page((unsigned long) buf);
		return -EFAULT;
	}
	buf[cnt] = '\0';

	mutex_lock(&event_mutex);
	file = event_file_data(filp);
	if (file)
		err = apply_event_filter(file, buf);
	mutex_unlock(&event_mutex);

	free_page((unsigned long) buf);
	if (err < 0)
		return err;

	*ppos += cnt;

	return cnt;
}
