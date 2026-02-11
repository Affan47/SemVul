showmode(struct fb_var_screeninfo *v)
{
	double drate = 0, hrate = 0, vrate = 0;

	if (v->pixclock) {
		drate = 1e12 / v->pixclock;
		hrate = drate / (v->left_margin + v->xres + v->right_margin + v->hsync_len);
		vrate = hrate / (v->upper_margin + v->yres + v->lower_margin + v->vsync_len);
	}
	printf("\nmode \"%ux%u-%u\"\n"
#if ENABLE_FEATURE_FBSET_FANCY
	"\t# D: %.3f MHz, H: %.3f kHz, V: %.3f Hz\n"
#endif
	"\tgeometry %u %u %u %u %u\n"
	"\ttimings %u %u %u %u %u %u %u\n"
	"\taccel %s\n"
	"\trgba %u/%u,%u/%u,%u/%u,%u/%u\n"
	"endmode\n\n",
		v->xres, v->yres, (int) (vrate + 0.5),
#if ENABLE_FEATURE_FBSET_FANCY
		drate / 1e6, hrate / 1e3, vrate,
#endif
		v->xres, v->yres, v->xres_virtual, v->yres_virtual, v->bits_per_pixel,
		v->pixclock, v->left_margin, v->right_margin, v->upper_margin, v->lower_margin,
			v->hsync_len, v->vsync_len,
		(v->accel_flags > 0 ? "true" : "false"),
		v->red.length, v->red.offset, v->green.length, v->green.offset,
			v->blue.length, v->blue.offset, v->transp.length, v->transp.offset);
}
