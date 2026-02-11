gnome_desktop_thumbnail_factory_lookup (GnomeDesktopThumbnailFactory *factory,
					const char                   *uri,
					time_t                        mtime)
{
	GChecksum *checksum;
	guint8     digest[16];
	gsize      digest_len = sizeof (digest);
	char      *file;
	char      *path;

	g_return_val_if_fail (uri != NULL, NULL);

	checksum = g_checksum_new (G_CHECKSUM_MD5);
	g_checksum_update (checksum, (const guchar *) uri, strlen (uri));
	g_checksum_get_digest (checksum, digest, &digest_len);
	g_assert (digest_len == 16);

	file = g_strconcat (g_checksum_get_string (checksum), ".png", NULL);
	path = thumbnail_factory_build_filename (factory,
							       (factory->priv->size == GNOME_DESKTOP_THUMBNAIL_SIZE_NORMAL)?"normal":"large",
							       file,
							       NULL);

	if (! gnome_desktop_thumbnail_is_valid (path, uri, mtime)) {
		g_free (path);
		path = NULL;
	}

	g_free (file);
	g_checksum_free (checksum);

	return path;
}
