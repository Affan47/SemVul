picolcd_fb_copyarea(struct fb_info *info,
		const struct fb_copyarea *area)
{
	if (!info->par)
		return;
	sys_copyarea(info, area);

	schedule_delayed_work(&info->deferred_work, 0);
}
