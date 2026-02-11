XGIfb_setcolreg(unsigned regno, unsigned red, unsigned green,
		unsigned blue, unsigned transp, struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;

	if (regno >= XGIfb_get_cmap_len(&info->var))
		return 1;

	switch (info->var.bits_per_pixel) {
	case 8:
		outb(regno, XGIDACA);
		outb((red >> 10), XGIDACD);
		outb((green >> 10), XGIDACD);
		outb((blue >> 10), XGIDACD);
		if (xgifb_info->display2 != XGIFB_DISP_NONE) {
			outb(regno, XGIDAC2A);
			outb((red >> 8), XGIDAC2D);
			outb((green >> 8), XGIDAC2D);
			outb((blue >> 8), XGIDAC2D);
		}
		break;
	case 16:
		((u32 *) (info->pseudo_palette))[regno] = ((red & 0xf800))
				| ((green & 0xfc00) >> 5) | ((blue & 0xf800)
				>> 11);
		break;
	case 32:
		red >>= 8;
		green >>= 8;
		blue >>= 8;
		((u32 *) (info->pseudo_palette))[regno] = (red << 16) | (green
				<< 8) | (blue);
		break;
	}
	return 0;
}
