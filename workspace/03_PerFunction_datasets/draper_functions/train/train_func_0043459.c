asiliantfb_check_var(struct fb_var_screeninfo *var,
			     struct fb_info *p)
{
	unsigned long Ftarget, ratio, remainder;

	ratio = 1000000 / var->pixclock;
	remainder = 1000000 % var->pixclock;
	Ftarget = 1000000 * ratio + (1000000 * remainder) / var->pixclock;


	if (Ftarget > 220000000 || Ftarget < 3125000) {
		printk(KERN_ERR "asiliantfb dotclock must be between 3.125 and 220MHz\n");
		return -ENXIO;
	}
	var->xres_virtual = var->xres;
	var->yres_virtual = var->yres;

	if (var->bits_per_pixel == 24) {
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = var->blue.length = var->green.length = 8;
	} else if (var->bits_per_pixel == 16) {
		switch (var->red.offset) {
			case 11:
				var->green.length = 6;
				break;
			case 10:
				var->green.length = 5;
				break;
			default:
				return -EINVAL;
		}
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = var->blue.length = 5;
	} else if (var->bits_per_pixel == 8) {
		var->red.offset = var->green.offset = var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
	}
	return 0;
}
