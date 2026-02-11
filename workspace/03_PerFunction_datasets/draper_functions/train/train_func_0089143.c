fbtft_fb_write(struct fb_info *info, const char __user *buf,
			      size_t count, loff_t *ppos)
{
	struct fbtft_par *par = info->par;
	ssize_t res;

	dev_dbg(info->dev,
		"%s: count=%zd, ppos=%llu\n", __func__,  count, *ppos);
	res = fb_sys_write(info, buf, count, ppos);


	par->fbtftops.mkdirty(info, -1, 0);

	return res;
}
