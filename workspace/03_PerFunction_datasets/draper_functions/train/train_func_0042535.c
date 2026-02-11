set_color(int color, unsigned char r, unsigned char g, unsigned char b, int highlight)
{
	palette_set_color (color, r, g, b);

	if(highlight) {
		r = 255-0.6*(255-r);
		g = 255-0.6*(255-g);
		b = 255-0.6*(255-b);
	} else {
		r = 0.6*r;
		g = 0.6*g;
		b = 0.6*b;
	}
	palette_set_color (color+Machine->drv->total_colors/2, r, g, b);
}
