gm_pixbuf_set_alpha(GdkPixbuf **pixs, guchar alpha) {
	int width, height, n_channels, rowstride, y, x;
	GdkPixbuf *pix;
	guchar *pixels, *p;

	if (!gdk_pixbuf_get_has_alpha(*pixs)) {
		pix = gdk_pixbuf_add_alpha(*pixs, FALSE, 0, 0, 0);
		gdk_pixbuf_unref(*pixs);
	} else {
		pix = *pixs;
	}

	n_channels = gdk_pixbuf_get_n_channels(pix);

	if (gdk_pixbuf_get_colorspace(pix) != GDK_COLORSPACE_RGB ||
			gdk_pixbuf_get_bits_per_sample(pix) != 8 ||
			!gdk_pixbuf_get_has_alpha(pix) ||
			n_channels != 4) {
		*pixs = pix;
		return;
	}

	width = gdk_pixbuf_get_width(pix);
	height = gdk_pixbuf_get_height(pix);
	rowstride = gdk_pixbuf_get_rowstride(pix);
	pixels = gdk_pixbuf_get_pixels(pix);
	p = pixels;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			p[3] = alpha;
			p = p + n_channels;
		}
	}

	*pixs = pix;
}
