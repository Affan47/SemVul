finalize (GObject *object)
{
	NMDHCP4ConfigPrivate *priv = NM_DHCP4_CONFIG_GET_PRIVATE (object);

	if (priv->options)
		g_hash_table_destroy (priv->options);

	g_object_unref (priv->proxy);

	G_OBJECT_CLASS (nm_dhcp4_config_parent_class)->finalize (object);
}
