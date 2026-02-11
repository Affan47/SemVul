pk_package_cache_finalize (GObject *object)
{
	PkPackageCache *pkcache = PK_PACKAGE_CACHE (object);
	PkPackageCachePrivate *priv = pkcache->priv;

	g_free (priv->filename);

	if (priv->locked) {
		g_warning ("YOU HAVE TO MANUALLY CALL pk_package_cache_close()!!!");
		sqlite3_close (priv->db);
	}

	G_OBJECT_CLASS (pk_package_cache_parent_class)->finalize (object);
}
