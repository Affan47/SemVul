get_as_pixbuf_for_size (GnomeBG    *bg,
			const char *filename,
			gint        num_monitor,
			gint        best_width,
			gint        best_height)
{
	const FileCacheEntry *ent;
	if ((ent = file_cache_lookup (bg, PIXBUF, filename))) {
		return g_object_ref (ent->u.pixbuf);
	}
	else {
		GdkPixbufFormat *format;
		GdkPixbuf *pixbuf;
                gchar *tmp;
		pixbuf = NULL;


		if (num_monitor != -1)
			pixbuf = load_from_cache_file (bg, filename, num_monitor, best_width, best_height);

		if (!pixbuf) {

			format = gdk_pixbuf_get_file_info (filename, NULL, NULL);

			if (format != NULL) {
				tmp = gdk_pixbuf_format_get_name (format);
			} else {
				tmp = NULL;
			}

			if (tmp != NULL &&
			    strcmp (tmp, "svg") == 0 &&
			    (best_width > 0 && best_height > 0) &&
			    (bg->placement == G_DESKTOP_BACKGROUND_STYLE_STRETCHED ||
			     bg->placement == G_DESKTOP_BACKGROUND_STYLE_SCALED ||
			     bg->placement == G_DESKTOP_BACKGROUND_STYLE_ZOOM))
				pixbuf = gdk_pixbuf_new_from_file_at_size (filename, best_width, best_height, NULL);
			else
				pixbuf = gdk_pixbuf_new_from_file (filename, NULL);
			g_free (tmp);
		}

		if (pixbuf)
			file_cache_add_pixbuf (bg, filename, pixbuf);

		return pixbuf;
	}
}
