panel_util_cairo_rgbdata_to_pixbuf (unsigned char *data,
				    int            width,
				    int            height)
{
	GdkPixbuf     *retval;
	unsigned char *dstptr;
	unsigned char *srcptr;
	int            align;

	g_assert (width > 0 && height > 0);

	if (!data)
		return NULL;

	retval = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, width, height);
	if (!retval)
		return NULL;

	dstptr = gdk_pixbuf_get_pixels (retval);
	srcptr = data;
	align  = gdk_pixbuf_get_rowstride (retval) - (width * 3);

#if G_BYTE_ORDER == G_LITTLE_ENDIAN

#define CAIRO_RED 2
#define CAIRO_GREEN 1
#define CAIRO_BLUE 0
#else

#define CAIRO_RED 1
#define CAIRO_GREEN 2
#define CAIRO_BLUE 3
#endif

	while (height--) {
		int x = width;
		while (x--) {

			dstptr[0] = srcptr[CAIRO_RED];
			dstptr[1] = srcptr[CAIRO_GREEN];
			dstptr[2] = srcptr[CAIRO_BLUE];

			dstptr += 3;
			srcptr += 4;
		}

		dstptr += align;
	}
#undef CAIRO_RED
#undef CAIRO_GREEN
#undef CAIRO_BLUE

	return retval;
}
