cw_clear_margins(struct vc_data *vc, struct fb_info *info,
			     int bottom_only)
{
	unsigned int cw = vc->vc_font.width;
	unsigned int ch = vc->vc_font.height;
	unsigned int rw = info->var.yres - (vc->vc_cols*cw);
	unsigned int bh = info->var.xres - (vc->vc_rows*ch);
	unsigned int rs = info->var.yres - rw;
	struct fb_fillrect region;

	region.color = 0;
	region.rop = ROP_COPY;

	if (rw && !bottom_only) {
		region.dx = 0;
		region.dy = info->var.yoffset + rs;
		region.height = rw;
		region.width = info->var.xres_virtual;
		info->fbops->fb_fillrect(info, &region);
	}

	if (bh) {
		region.dx = info->var.xoffset;
		region.dy = info->var.yoffset;
                region.height = info->var.yres;
                region.width = bh;
		info->fbops->fb_fillrect(info, &region);
	}
}
