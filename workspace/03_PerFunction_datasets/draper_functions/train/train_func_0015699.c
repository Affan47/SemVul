store_pan(struct device *device,
			 struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fb_var_screeninfo var;
	char *last = NULL;
	int err;

	var = fb_info->var;
	var.xoffset = simple_strtoul(buf, &last, 0);
	last++;
	if (last - buf >= count)
		return -EINVAL;
	var.yoffset = simple_strtoul(last, &last, 0);

	console_lock();
	err = fb_pan_display(fb_info, &var);
	console_unlock();

	if (err < 0)
		return err;
	return count;
}
