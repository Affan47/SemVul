fanotify_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
#ifdef CONFIG_FANOTIFY_ACCESS_PERMISSIONS
	struct fanotify_response response = { .fd = -1, .response = -1 };
	struct fsnotify_group *group;
	int ret;

	group = file->private_data;

	if (count > sizeof(response))
		count = sizeof(response);

	pr_debug("%s: group=%p count=%zu\n", __func__, group, count);

	if (copy_from_user(&response, buf, count))
		return -EFAULT;

	ret = process_access_response(group, &response);
	if (ret < 0)
		count = ret;

	return count;
#else
	return -EINVAL;
#endif
}
