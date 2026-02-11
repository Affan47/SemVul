cirrusfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;

	if (regno > 255)
		return -EINVAL;

	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 v;
		red >>= (16 - info->var.red.length);
		green >>= (16 - info->var.green.length);
		blue >>= (16 - info->var.blue.length);

		if (regno >= 16)
			return 1;
		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset);

		cinfo->pseudo_palette[regno] = v;
		return 0;
	}

	if (info->var.bits_per_pixel == 8)
		WClut(cinfo, regno, red >> 10, green >> 10, blue >> 10);

	return 0;

}
