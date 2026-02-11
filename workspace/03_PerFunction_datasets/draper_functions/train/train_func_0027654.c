float_to_color_comp(double value) {
	int color = (int)floor(value*255 + 0.5);
	if (color < 0) color = 0;
	if (color > 255) color = 255;
	return (unsigned char)color;
}
