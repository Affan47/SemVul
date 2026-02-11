viafb_imageblit(struct fb_info *info,
	const struct fb_image *image)
{
	struct viafb_par *viapar = info->par;
	struct viafb_shared *shared = viapar->shared;
	u32 fg_color = 0, bg_color = 0;
	u8 op;

	if (info->flags & FBINFO_HWACCEL_DISABLED || !shared->hw_bitblt ||
		(image->depth != 1 && image->depth != viapar->depth)) {
		cfb_imageblit(info, image);
		return;
	}

	if (image->depth == 1) {
		op = VIA_BITBLT_MONO;
		if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
			fg_color =
				((u32 *)info->pseudo_palette)[image->fg_color];
			bg_color =
				((u32 *)info->pseudo_palette)[image->bg_color];
		} else {
			fg_color = image->fg_color;
			bg_color = image->bg_color;
		}
	} else
		op = VIA_BITBLT_COLOR;

	DEBUG_MSG(KERN_DEBUG "viafb 2D engine: imageblit\n");
	if (shared->hw_bitblt(shared->vdev->engine_mmio, op,
		image->width, image->height, info->var.bits_per_pixel,
		viapar->vram_addr, info->fix.line_length, image->dx, image->dy,
		(u32 *)image->data, 0, 0, 0, 0, fg_color, bg_color, 0))
		cfb_imageblit(info, image);
}
