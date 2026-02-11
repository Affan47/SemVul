sisfb_calc_maxyres(struct sis_video_info *ivideo, struct fb_var_screeninfo *var)
{
	int maxyres = ivideo->sisfb_mem / (var->xres_virtual * (var->bits_per_pixel >> 3));

	if(maxyres > 32767) maxyres = 32767;

	return maxyres;
}
