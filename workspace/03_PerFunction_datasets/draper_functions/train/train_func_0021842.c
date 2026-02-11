carmine_set_par(struct fb_info *info)
{
	struct carmine_fb *par = info->par;
	int ret;

	ret = carmine_find_mode(&info->var);
	if (ret < 0)
		return ret;

	par->new_mode = ret;
	if (par->cur_mode != par->new_mode) {

		par->cur_mode = par->new_mode;
		par->res = &car_modes[par->new_mode];

		carmine_init_display_param(par);
		set_display_parameters(par);
	}

	info->fix.line_length = info->var.xres * info->var.bits_per_pixel / 8;
	return 0;
}
