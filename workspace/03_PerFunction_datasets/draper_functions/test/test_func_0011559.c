vga16fb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	if (image->depth == 1)
		vga_imageblit_expand(info, image);
	else
		vga_imageblit_color(info, image);
}
