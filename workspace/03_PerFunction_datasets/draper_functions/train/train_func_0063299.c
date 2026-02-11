scale_thumbnail_if_necessary (RBFadingImage *image, GdkPixbuf *pixbuf)
{
	int w, h;
	int pw, ph;
	int sw, sh;
	double factor;

	w = gtk_widget_get_allocated_width (GTK_WIDGET (image)) - 2 * BORDER_WIDTH;
	h = gtk_widget_get_allocated_height (GTK_WIDGET (image)) - 2 * BORDER_WIDTH;
	if (w < 1 || h < 1) {
		return NULL;
	}

	pw = gdk_pixbuf_get_width (pixbuf);
	ph = gdk_pixbuf_get_height (pixbuf);

	if (pw <= w && ph <= h) {
		return g_object_ref (pixbuf);
	}

	if (pw > ph) {
		sw = w;
		factor = (double) w / pw;
		sh = (int)((double)ph * factor);
	} else {
		sh = h;
		factor = (double) h / ph;
		sw = (int)((double)pw * factor);
	}

	return gdk_pixbuf_scale_simple (pixbuf, sw, sh, GDK_INTERP_HYPER);
}
