mac_vmode_to_var(int vmode, int cmode, struct fb_var_screeninfo *var)
{
    const struct fb_videomode *mode = NULL;
    const struct mode_map *map;

    for (map = mac_modes; map->vmode != -1; map++)
	if (map->vmode == vmode) {
	    mode = map->mode;
	    break;
	}
    if (!mode)
	return -EINVAL;

    memset(var, 0, sizeof(struct fb_var_screeninfo));
    switch (cmode) {
	case CMODE_8:
	    var->bits_per_pixel = 8;
	    var->red.offset = 0;
	    var->red.length = 8;
	    var->green.offset = 0;
	    var->green.length = 8;
	    var->blue.offset = 0;
	    var->blue.length = 8;
	    break;

	case CMODE_16:
	    var->bits_per_pixel = 16;
	    var->red.offset = 10;
	    var->red.length = 5;
	    var->green.offset = 5;
	    var->green.length = 5;
	    var->blue.offset = 0;
	    var->blue.length = 5;
	    break;

	case CMODE_32:
	    var->bits_per_pixel = 32;
	    var->red.offset = 16;
	    var->red.length = 8;
	    var->green.offset = 8;
	    var->green.length = 8;
	    var->blue.offset = 0;
	    var->blue.length = 8;
	    var->transp.offset = 24;
	    var->transp.length = 8;
	    break;

	default:
	    return -EINVAL;
    }
    var->xres = mode->xres;
    var->yres = mode->yres;
    var->xres_virtual = mode->xres;
    var->yres_virtual = mode->yres;
    var->height = -1;
    var->width = -1;
    var->pixclock = mode->pixclock;
    var->left_margin = mode->left_margin;
    var->right_margin = mode->right_margin;
    var->upper_margin = mode->upper_margin;
    var->lower_margin = mode->lower_margin;
    var->hsync_len = mode->hsync_len;
    var->vsync_len = mode->vsync_len;
    var->sync = mode->sync;
    var->vmode = mode->vmode;
    return 0;
}
