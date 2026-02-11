photo_cache_dispose (GObject *object)
{
	EPhotoCachePrivate *priv;

	priv = E_PHOTO_CACHE_GET_PRIVATE (object);

	g_clear_object (&priv->client_cache);

	photo_ht_remove_all (E_PHOTO_CACHE (object));


	G_OBJECT_CLASS (e_photo_cache_parent_class)->dispose (object);
}
