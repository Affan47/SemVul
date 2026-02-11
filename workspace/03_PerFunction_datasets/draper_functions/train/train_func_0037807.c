image_8native_to_8grey(int width, unsigned char *dest, unsigned char *source)
{
    int i;
    int value;
    unsigned char r, g, b;
    for (i=0; i<width; i++) {
	value = *source++;
	image_colour(DISPLAY_COLORS_NATIVE | DISPLAY_DEPTH_8,
	    value, &r, &g, &b);
	*dest++ = colour_to_grey(r,g,b);
    }
}
