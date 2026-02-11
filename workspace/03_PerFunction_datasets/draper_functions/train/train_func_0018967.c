gt_pixbuf_make_gray(GdkPixbuf *pixbuf)
{
	guchar *p;
	int i, n;

	p = gdk_pixbuf_get_pixels(pixbuf);
	n = gdk_pixbuf_get_width(pixbuf) * gdk_pixbuf_get_height(pixbuf);

	for (i = 0; i < n; i++, p += 4)
		p[0] = p[1] = p[2] = (p[0] * 11 + p[1] * 16 + p[2] * 5) / 32;
}
