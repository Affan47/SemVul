color_compare(PaletteColor *c1, PaletteColor *c2)
{
	if (c1->red != c2->red)
		return c1->red - c2->red;
	if (c1->green != c2->green)
		return c1->green - c2->green;
	if (c1->blue != c2->blue)
		return c1->blue - c2->blue;
	return 0;
}
