ocfb_init_fix(struct ocfb_dev *fbdev)
{
	struct fb_var_screeninfo *var = &fbdev->info.var;
	struct fb_fix_screeninfo *fix = &fbdev->info.fix;

	strcpy(fix->id, OCFB_NAME);

	fix->line_length = var->xres * var->bits_per_pixel/8;
	fix->smem_len = fix->line_length * var->yres;
	fix->type = FB_TYPE_PACKED_PIXELS;

	if (var->bits_per_pixel == 8 && !var->grayscale)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	else
		fix->visual = FB_VISUAL_TRUECOLOR;

	return 0;
}
