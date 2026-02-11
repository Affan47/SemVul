viafb_dvi_set_mode(const struct fb_var_screeninfo *var,
	u16 cxres, u16 cyres, int iga)
{
	struct fb_var_screeninfo dvi_var = *var;
	const struct fb_videomode *rb_mode;
	int maxPixelClock;

	maxPixelClock = viaparinfo->shared->tmds_setting_info.max_pixel_clock;
	if (maxPixelClock && PICOS2KHZ(var->pixclock) / 1000 > maxPixelClock) {
		rb_mode = viafb_get_best_rb_mode(var->xres, var->yres, 60);
		if (rb_mode)
			viafb_fill_var_timing_info(&dvi_var, rb_mode);
	}

	viafb_fill_crtc_timing(&dvi_var, cxres, cyres, iga);
}
