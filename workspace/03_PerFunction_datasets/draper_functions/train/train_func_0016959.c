finalize (GObject *object)
{
	NMDHCPManagerPrivate *priv = NM_DHCP_MANAGER_GET_PRIVATE (object);

	if (priv->hostname_provider) {
		g_object_weak_unref (G_OBJECT (priv->hostname_provider), hostname_provider_destroyed, object);
		priv->hostname_provider = NULL;
	}

	if (priv->clients)
		g_hash_table_destroy (priv->clients);
	if (priv->proxy)
		g_object_unref (priv->proxy);
	if (priv->dbus_mgr)
		g_object_unref (priv->dbus_mgr);

	G_OBJECT_CLASS (nm_dhcp_manager_parent_class)->finalize (object);
}
