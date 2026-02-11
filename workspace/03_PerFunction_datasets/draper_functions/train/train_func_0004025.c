aty128fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *fb)
{
	struct aty128fb_par *par = fb->par;
	u32 xoffset, yoffset;
	u32 offset;
	u32 xres, yres;

	xres = (((par->crtc.h_total >> 16) & 0xff) + 1) << 3;
	yres = ((par->crtc.v_total >> 16) & 0x7ff) + 1;

	xoffset = (var->xoffset +7) & ~7;
	yoffset = var->yoffset;

	if (xoffset+xres > par->crtc.vxres || yoffset+yres > par->crtc.vyres)
		return -EINVAL;

	par->crtc.xoffset = xoffset;
	par->crtc.yoffset = yoffset;

	offset = ((yoffset * par->crtc.vxres + xoffset) * (par->crtc.bpp >> 3))
									  & ~7;

	if (par->crtc.bpp == 24)
		offset += 8 * (offset % 3);

	aty_st_le32(CRTC_OFFSET, offset);

	return 0;
}
