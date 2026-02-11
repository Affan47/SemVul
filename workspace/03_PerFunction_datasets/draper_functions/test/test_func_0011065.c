create_thumbnail_for_filename (GnomeDesktopThumbnailFactory *factory,
			       const char            *filename)
{
	char *thumb;
	time_t mtime;
	GdkPixbuf *orig, *result = NULL;
	char *uri;

	mtime = get_mtime (filename);

	if (mtime == (time_t)-1)
		return NULL;

	uri = g_filename_to_uri (filename, NULL, NULL);

	if (uri == NULL)
		return NULL;

	thumb = gnome_desktop_thumbnail_factory_lookup (factory, uri, mtime);

	if (thumb) {
		result = gdk_pixbuf_new_from_file (thumb, NULL);
		g_free (thumb);
	}
	else {
		orig = gdk_pixbuf_new_from_file (filename, NULL);
		if (orig) {
			int orig_width = gdk_pixbuf_get_width (orig);
			int orig_height = gdk_pixbuf_get_height (orig);

			result = pixbuf_scale_to_fit (orig, THUMBNAIL_SIZE, THUMBNAIL_SIZE);

			g_object_set_data_full (G_OBJECT (result), "gnome-thumbnail-height",
						g_strdup_printf ("%d", orig_height), g_free);
			g_object_set_data_full (G_OBJECT (result), "gnome-thumbnail-width",
						g_strdup_printf ("%d", orig_width), g_free);

			g_object_unref (orig);

			gnome_desktop_thumbnail_factory_save_thumbnail (factory, result, uri, mtime);
		}
		else {
			gnome_desktop_thumbnail_factory_create_failed_thumbnail (factory, uri, mtime);
		}
	}

	g_free (uri);

	return result;
}
