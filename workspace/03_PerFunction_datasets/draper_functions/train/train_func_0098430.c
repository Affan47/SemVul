dither_line_color(unsigned char *src, unsigned char *dest, int y, int width)
{
    register long   a, b;
    long           *ymod, xmod;

    ymod = DM[y & DITHER_MASK];

    while (width--) {
	xmod = width & DITHER_MASK;

	b = red_dither[*(src++)];
	if (ymod[xmod] < b)
	    b >>= 8;

	a = green_dither[*(src++)];
	if (ymod[xmod] < a)
	    a >>= 8;
	b += a;

	a = blue_dither[*(src++)];
	if (ymod[xmod] < a)
	    a >>= 8;
	b += a;

	*(dest++) = b & 0xff;
    }
}
