pixel (int x, int y, unsigned colidx)
{
	unsigned xormode;
	union multiptr loc;

	if ((x < 0) || ((__u32)x >= var.xres_virtual) ||
	    (y < 0) || ((__u32)y >= var.yres_virtual))
		return;

	xormode = colidx & XORMODE;
	colidx &= ~XORMODE;

#ifdef DEBUG
	if (colidx > 255) {
		fprintf (stderr, "WARNING: color value = %u, must be <256\n",
			 colidx);
		return;
	}
#endif

	loc.p8 = line_addr [y] + x * bytes_per_pixel;
	__setpixel (loc, xormode, colormap [colidx]);
}
