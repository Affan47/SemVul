pk_package_cache_set_filename (PkPackageCache *pkcache, const gchar *filename, GError **error)
{
	gboolean ret = TRUE;
	PkPackageCachePrivate *priv = PK_PACKAGE_CACHE (pkcache)->priv;

	g_return_val_if_fail (PK_IS_PACKAGE_CACHE (pkcache), FALSE);


	if (priv->locked) {
		g_set_error (error, 1, 0, "cache database is already open");
		ret = FALSE;
		goto out;
	}

	g_free (priv->filename);

	if (filename == NULL) {
		g_set_error (error, 1, 0, "cache database not specified");
		ret = FALSE;
		goto out;
	}

	priv->filename = g_strdup (filename);

out:
	return ret;
}
