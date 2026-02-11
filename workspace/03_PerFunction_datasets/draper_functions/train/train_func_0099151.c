cirrusfb_sync(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;

	if (!is_laguna(cinfo)) {
		while (vga_rgfx(cinfo->regbase, CL_GR31) & 0x03)
			cpu_relax();
	}
	return 0;
}
