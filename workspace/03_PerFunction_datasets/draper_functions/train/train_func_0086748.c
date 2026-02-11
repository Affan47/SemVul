remove_alpha (GdkPixbuf *pixbuf, int x, int y, int width, int height, int *rowstride)
{
	guchar *buf;
	int xx, yy;
	guchar *src, *dest;

	g_assert (gdk_pixbuf_get_n_channels (pixbuf) == 4);
	g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
	g_assert (width > 0 && height > 0);
	g_assert (x >= 0 && x + width <= gdk_pixbuf_get_width (pixbuf));
	g_assert (y >= 0 && y + height <= gdk_pixbuf_get_height (pixbuf));

	*rowstride = 4 * ((width * 3 + 3) / 4);

	buf = g_new (guchar, *rowstride * height);

	for (yy = 0; yy < height; yy++) {
		src = gdk_pixbuf_get_pixels (pixbuf) + gdk_pixbuf_get_rowstride (pixbuf) * (yy + y) + x * gdk_pixbuf_get_n_channels (pixbuf);
		dest = buf + *rowstride * yy;

		for (xx = 0; xx < width; xx++) {
			*dest++ = *src++;
			*dest++ = *src++;
			*dest++ = *src++;
			src++;
		}
	}

	return buf;
}
