lxfb_init_fbinfo(struct device *dev)
{
	struct lxfb_par *par;
	struct fb_info *info;


	info = framebuffer_alloc(sizeof(struct lxfb_par) + sizeof(u32) * 16,
				 dev);
	if (!info)
		return NULL;

	par = info->par;

	strcpy(info->fix.id, "Geode LX");

	info->fix.type		= FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	= 0;
	info->fix.xpanstep	= 0;
	info->fix.ypanstep	= 0;
	info->fix.ywrapstep	= 0;
	info->fix.accel		= FB_ACCEL_NONE;

	info->var.nonstd	= 0;
	info->var.activate	= FB_ACTIVATE_NOW;
	info->var.height	= -1;
	info->var.width	= -1;
	info->var.accel_flags = 0;
	info->var.vmode	= FB_VMODE_NONINTERLACED;

	info->fbops		= &lxfb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseudo_palette	= (void *)par + sizeof(struct lxfb_par);

	if (fb_alloc_cmap(&info->cmap, 256, 0) < 0) {
		framebuffer_release(info);
		return NULL;
	}

	info->var.grayscale	= 0;

	return info;
}
