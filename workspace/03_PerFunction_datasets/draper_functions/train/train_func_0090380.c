avatar_image_load_cb (GObject      *object,
		      GAsyncResult *result,
		      gpointer      user_data)
{
	GiggleAvatarCache *cache = GIGGLE_AVATAR_CACHE (object);
	GError            *error = NULL;
	GdkPixbuf         *pixbuf;

	pixbuf = giggle_avatar_cache_load_finish (cache, result, &error);

	if (pixbuf) {
		giggle_avatar_image_set_pixbuf (user_data, pixbuf);
	} else if (error) {
		if (!g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
			g_warning ("%s: %s", G_STRFUNC, error->message);

		g_error_free (error);
	}
}
