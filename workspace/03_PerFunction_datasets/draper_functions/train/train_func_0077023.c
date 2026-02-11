neo2200_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct neofb_par *par = info->par;
	u_long dst, rop;

	dst = rect->dx + rect->dy * info->var.xres_virtual;
	rop = rect->rop ? 0x060000 : 0x0c0000;

	neo2200_wait_fifo(info, 4);


	writel(NEO_BC3_FIFO_EN |
	       NEO_BC0_SRC_IS_FG | NEO_BC3_SKIP_MAPPING |


	       rop, &par->neo2200->bltCntl);

	switch (info->var.bits_per_pixel) {
	case 8:
		writel(rect->color, &par->neo2200->fgColor);
		break;
	case 16:
	case 24:
		writel(((u32 *) (info->pseudo_palette))[rect->color],
		       &par->neo2200->fgColor);
		break;
	}

	writel(dst * ((info->var.bits_per_pixel + 7) >> 3),
	       &par->neo2200->dstStart);
	writel((rect->height << 16) | (rect->width & 0xffff),
	       &par->neo2200->xyExt);
}
