nvidiafb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct nvidia_par *par = info->par;
	u32 color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;

	if (par->lockup) {
		cfb_fillrect(info, rect);
		return;
	}

	if (info->var.bits_per_pixel == 8)
		color = rect->color;
	else
		color = ((u32 *) info->pseudo_palette)[rect->color];

	if (rect->rop != ROP_COPY)
		NVSetRopSolid(info, rect->rop, ~0);

	NVDmaStart(info, par, RECT_SOLID_COLOR, 1);
	NVDmaNext(par, color);

	NVDmaStart(info, par, RECT_SOLID_RECTS(0), 2);
	NVDmaNext(par, (rect->dx << 16) | rect->dy);
	NVDmaNext(par, (rect->width << 16) | rect->height);

	NVDmaKickoff(par);

	if (rect->rop != ROP_COPY)
		NVSetRopSolid(info, ROP_COPY, ~0);
}
