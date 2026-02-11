up_backend_finalize (GObject *object)
{
	UpBackend *backend;

	g_return_if_fail (UP_IS_BACKEND (object));

	backend = UP_BACKEND (object);

	if (backend->priv->daemon != NULL)
		g_object_unref (backend->priv->daemon);
	if (backend->priv->device_list != NULL)
		g_object_unref (backend->priv->device_list);

#ifdef EGG_TEST
	g_object_unref (backend->priv->native);
	g_object_unref (backend->priv->device);
#endif

	G_OBJECT_CLASS (up_backend_parent_class)->finalize (object);
}
