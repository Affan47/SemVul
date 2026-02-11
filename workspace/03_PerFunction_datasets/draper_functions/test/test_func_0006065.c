fbcon_resize(struct vc_data *vc, unsigned int width,
			unsigned int height, unsigned int user)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;
	struct display *p = &fb_display[vc->vc_num];
	struct fb_var_screeninfo var = info->var;
	int x_diff, y_diff, virt_w, virt_h, virt_fw, virt_fh;

	virt_w = FBCON_SWAP(ops->rotate, width, height);
	virt_h = FBCON_SWAP(ops->rotate, height, width);
	virt_fw = FBCON_SWAP(ops->rotate, vc->vc_font.width,
				 vc->vc_font.height);
	virt_fh = FBCON_SWAP(ops->rotate, vc->vc_font.height,
				 vc->vc_font.width);
	var.xres = virt_w * virt_fw;
	var.yres = virt_h * virt_fh;
	x_diff = info->var.xres - var.xres;
	y_diff = info->var.yres - var.yres;
	if (x_diff < 0 || x_diff > virt_fw ||
	    y_diff < 0 || y_diff > virt_fh) {
		const struct fb_videomode *mode;

		DPRINTK("attempting resize %ix%i\n", var.xres, var.yres);
		mode = fb_find_best_mode(&var, &info->modelist);
		if (mode == NULL)
			return -EINVAL;
		display_to_var(&var, p);
		fb_videomode_to_var(&var, mode);

		if (virt_w > var.xres/virt_fw || virt_h > var.yres/virt_fh)
			return -EINVAL;

		DPRINTK("resize now %ix%i\n", var.xres, var.yres);
		if (CON_IS_VISIBLE(vc)) {
			var.activate = FB_ACTIVATE_NOW |
				FB_ACTIVATE_FORCE;
			fb_set_var(info, &var);
		}
		var_to_display(p, &info->var, info);
		ops->var = info->var;
	}
	updatescrollmode(p, info, vc);
	return 0;
}
