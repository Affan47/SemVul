goc_pixbuf_draw (GocItem const *item, cairo_t *cr)
{
	GocPixbuf *pixbuf = GOC_PIXBUF (item);
	GOImage * image;
	double height, width;
	double scalex = 1., scaley = 1.;
	int x;

	if (pixbuf->pixbuf == NULL || pixbuf->width == 0. || pixbuf->height == 0.)
		return;

	image = go_pixbuf_new_from_pixbuf (pixbuf->pixbuf);
	if (pixbuf->width < 0.)
		width = gdk_pixbuf_get_width (pixbuf->pixbuf);
	else {
		width = pixbuf->width;
		scalex = width / gdk_pixbuf_get_width (pixbuf->pixbuf);
	}
	if (pixbuf->height < 0.)
		height = gdk_pixbuf_get_height (pixbuf->pixbuf);
	else {
		height = pixbuf->height;
		scaley = height / gdk_pixbuf_get_height (pixbuf->pixbuf);
	}
	cairo_save (cr);
	_goc_item_transform (item, cr, TRUE);
	x = (goc_canvas_get_direction (item->canvas) == GOC_DIRECTION_RTL)?
		pixbuf->x + pixbuf->width: pixbuf->x;
	goc_group_cairo_transform (item->parent, cr, x, (int) pixbuf->y);
	cairo_rotate (cr, pixbuf->rotation);
	if (scalex != 1. || scaley != 1.)
		cairo_scale (cr, scalex, scaley);
	cairo_move_to (cr, 0, 0);
	go_image_draw (image, cr);
	cairo_restore (cr);
	g_object_unref (image);
}
