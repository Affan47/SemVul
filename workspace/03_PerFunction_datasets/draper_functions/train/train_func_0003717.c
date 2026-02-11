gnome_bg_create_surface (GnomeBG	    *bg,
		 	 GdkWindow   *window,
			 int	     width,
			 int	     height,
			 gboolean     root)
{
	int pm_width, pm_height;
	cairo_surface_t *surface;
	GdkRGBA average;
	cairo_t *cr;

	g_return_val_if_fail (bg != NULL, NULL);
	g_return_val_if_fail (window != NULL, NULL);

        if (bg->pixbuf_cache &&
            gdk_pixbuf_get_width (bg->pixbuf_cache) != width &&
            gdk_pixbuf_get_height (bg->pixbuf_cache) != height) {
                g_object_unref (bg->pixbuf_cache);
                bg->pixbuf_cache = NULL;
        }


	gnome_bg_get_pixmap_size (bg, width, height, &pm_width, &pm_height);

	if (root) {
		surface = make_root_pixmap (gdk_window_get_screen (window),
					   pm_width, pm_height);
	}
	else {
		surface = gdk_window_create_similar_surface (window,
                                                             CAIRO_CONTENT_COLOR,
                                                             pm_width, pm_height);
	}

	if (surface == NULL)
		return NULL;

	cr = cairo_create (surface);
	if (!bg->filename && bg->color_type == G_DESKTOP_BACKGROUND_SHADING_SOLID) {
		gdk_cairo_set_source_color (cr, &(bg->primary));
		average.red = bg->primary.red / 65535.0;
		average.green = bg->primary.green / 65535.0;
		average.blue = bg->primary.blue / 65535.0;
		average.alpha = 1.0;
	}
	else {
		GdkPixbuf *pixbuf;

		pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8,
					 width, height);
		gnome_bg_draw (bg, pixbuf, gdk_window_get_screen (window), root);
		gdk_cairo_set_source_pixbuf (cr, pixbuf, 0, 0);
		pixbuf_average_value (pixbuf, &average);
		g_object_unref (pixbuf);
	}

	cairo_paint (cr);

	cairo_destroy (cr);

	cairo_surface_set_user_data (surface, &average_color_key,
	                             gdk_rgba_copy (&average),
	                             (cairo_destroy_func_t) gdk_rgba_free);

	return surface;
}
