urf_device_dispose (GObject *object)
{
	UrfDevicePrivate *priv;

	g_return_if_fail (URF_IS_DEVICE (object));

	priv = URF_DEVICE (object)->priv;

	if (priv->proxy) {
		g_object_unref (priv->proxy);
		priv->proxy = NULL;
	}

	G_OBJECT_CLASS(urf_device_parent_class)->dispose(object);
}
