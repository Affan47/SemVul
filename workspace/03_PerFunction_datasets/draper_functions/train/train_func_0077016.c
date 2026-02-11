store_debug(struct device *device,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fbtft_par *par = fb_info->par;
	int ret;

	ret = kstrtoul(buf, 10, &par->debug);
	if (ret)
		return ret;
	fbtft_expand_debug_value(&par->debug);

	return count;
}
