service_finalize (GObject *object)
{
	CamelServicePrivate *priv;

	priv = CAMEL_SERVICE_GET_PRIVATE (object);

	g_mutex_clear (&priv->settings_lock);

	g_free (priv->display_name);
	g_free (priv->user_data_dir);
	g_free (priv->user_cache_dir);
	g_free (priv->uid);
	g_free (priv->password);


	g_warn_if_fail (priv->connection_op == NULL);
	g_mutex_clear (&priv->connection_lock);


	G_OBJECT_CLASS (camel_service_parent_class)->finalize (object);
}
