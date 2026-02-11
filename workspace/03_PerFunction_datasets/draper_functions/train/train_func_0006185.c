pm3fb_depth(const struct fb_var_screeninfo *var)
{
	if (var->bits_per_pixel == 16)
		return var->red.length + var->green.length
			+ var->blue.length;

	return var->bits_per_pixel;
}
