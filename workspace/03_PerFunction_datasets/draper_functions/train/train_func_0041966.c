goc_pixbuf_distance (GocItem *item, double x, double y, GocItem **near_item)
{
	GocPixbuf *pixbuf = GOC_PIXBUF (item);

	double dx, dy, w, h;
	if (pixbuf->pixbuf == NULL)
		return G_MAXDOUBLE;
	w = (pixbuf->width >= 0.)? pixbuf->width: gdk_pixbuf_get_width (pixbuf->pixbuf);
	h = (pixbuf->height >= 0.)? pixbuf->height: gdk_pixbuf_get_height (pixbuf->pixbuf);
	if (x < pixbuf->x) {
		dx = pixbuf->x - x;
	} else if (x < pixbuf->x + w) {
		dx = 0;
	} else {
		dx = x - pixbuf->x - w;
	}
	if (y < pixbuf->y) {
		dy = pixbuf->y - y;
	} else if (y < pixbuf->y + h) {
		dy = 0;
	} else {
		dy = y - pixbuf->y - h;
	}
	*near_item = item;
	return hypot (dx, dy);
}
