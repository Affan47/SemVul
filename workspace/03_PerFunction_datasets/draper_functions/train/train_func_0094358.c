hvfb_get_option(struct fb_info *info)
{
	struct hvfb_par *par = info->par;
	char *opt = NULL, *p;
	uint x = 0, y = 0;

	if (fb_get_options(KBUILD_MODNAME, &opt) || !opt || !*opt)
		return;

	p = strsep(&opt, "x");
	if (!*p || kstrtouint(p, 0, &x) ||
	    !opt || !*opt || kstrtouint(opt, 0, &y)) {
		pr_err("Screen option is invalid: skipped\n");
		return;
	}

	if (x < HVFB_WIDTH_MIN || y < HVFB_HEIGHT_MIN ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN8 &&
	     x * y * screen_depth / 8 > SYNTHVID_FB_SIZE_WIN8) ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN7 &&
	     (x > SYNTHVID_WIDTH_MAX_WIN7 || y > SYNTHVID_HEIGHT_MAX_WIN7))) {
		pr_err("Screen resolution option is out of range: skipped\n");
		return;
	}

	screen_width = x;
	screen_height = y;
	return;
}
