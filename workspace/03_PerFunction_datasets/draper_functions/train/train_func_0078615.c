go_image_draw_fb (GOImage *image, cairo_t *cr)
{
#ifdef GOFFICE_WITH_GTK
	if (image->pixbuf) {
		cairo_rectangle (cr, 0., 0., image->width, image->height);
		gdk_cairo_set_source_pixbuf (cr, image->pixbuf, 0, 0);
		cairo_fill (cr);
	} else {
		GdkPixbuf *placeholder = gtk_icon_theme_load_icon
											(gtk_icon_theme_get_default (),
											 "unknown_image", 100, 0, NULL);
		double dx, dy;
		int n;
		if (placeholder == NULL)
			return;
		n = go_fake_floor (image->width / gdk_pixbuf_get_width (placeholder));
		dx = (image->width - n * gdk_pixbuf_get_width (placeholder)) / 2.;
		n = go_fake_floor (image->height / gdk_pixbuf_get_height (placeholder));
		dy = (image->height - n * gdk_pixbuf_get_height (placeholder)) / 2.;
		cairo_save (cr);
		cairo_rectangle (cr, 0., 0., image->width, image->height);
		cairo_clip (cr);
		cairo_rectangle (cr, -dx, -dy, image->width + dx, image->height + dy);
		gdk_cairo_set_source_pixbuf (cr, placeholder, 0, 0);
		cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
		cairo_fill (cr);
		cairo_restore (cr);
		g_object_unref (placeholder);
	}
#endif
}
