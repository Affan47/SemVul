show_bbp_cr(const char *dev, int cr, const char *desc,
			       const char *extra)
{
	int res;
	res = hostap_ioctl_readmif(dev, cr);
	if (res >= 0)
		printf("CR%d (%s): %d%s\n", cr, desc, res, extra);
}
