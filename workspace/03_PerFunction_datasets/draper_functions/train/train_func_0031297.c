cavan_fb_refresh(struct cavan_fb_device *dev)
{
	int ret;
	int index = (dev->fb_active + 1) % dev->fb_count;
	struct fb_var_screeninfo *var = &dev->var_info;

	mem_copy((byte *) dev->fb_base + dev->fb_size * index, dev->fb_cache, dev->fb_size);

	if (dev->fb_active == index)
	{
		return 0;
	}

	var->yoffset = index * dev->yres;

	ret = ioctl(dev->fb, FBIOPUT_VSCREENINFO, var);
	if (ret < 0)
	{
		pr_error_info("ioctl FBIOPUT_VSCREENINFO");
		return ret;
	}

	dev->fb_active = index;

	return 0;
}
