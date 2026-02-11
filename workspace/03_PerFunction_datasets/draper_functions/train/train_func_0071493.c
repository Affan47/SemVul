picolcd_fb_write(struct fb_info *info, const char __user *buf,
		size_t count, loff_t *ppos)
{
	ssize_t ret;
	if (!info->par)
		return -ENODEV;
	ret = fb_sys_write(info, buf, count, ppos);
	if (ret >= 0)
		schedule_delayed_work(&info->deferred_work, 0);
	return ret;
}
