tdfxfb_fillrect(struct fb_info *info,
			    const struct fb_fillrect *rect)
{
	struct tdfx_par *par = info->par;
	u32 bpp = info->var.bits_per_pixel;
	u32 stride = info->fix.line_length;
	u32 fmt = stride | ((bpp + ((bpp == 8) ? 0 : 8)) << 13);
	int tdfx_rop;
	u32 dx = rect->dx;
	u32 dy = rect->dy;
	u32 dstbase = 0;

	if (rect->rop == ROP_COPY)
		tdfx_rop = TDFX_ROP_COPY;
	else
		tdfx_rop = TDFX_ROP_XOR;


	if (dy + rect->height > 4095) {
		dstbase = stride * dy;
		dy = 0;
	}

	if (dx + rect->width > 4095) {
		dstbase += dx * bpp >> 3;
		dx = 0;
	}
	banshee_make_room(par, 6);
	tdfx_outl(par, DSTFORMAT, fmt);
	if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) {
		tdfx_outl(par, COLORFORE, rect->color);
	} else {
		tdfx_outl(par, COLORFORE, par->palette[rect->color]);
	}
	tdfx_outl(par, COMMAND_2D, COMMAND_2D_FILLRECT | (tdfx_rop << 24));
	tdfx_outl(par, DSTBASE, dstbase);
	tdfx_outl(par, DSTSIZE, rect->width | (rect->height << 16));
	tdfx_outl(par, LAUNCH_2D, dx | (dy << 16));
}
