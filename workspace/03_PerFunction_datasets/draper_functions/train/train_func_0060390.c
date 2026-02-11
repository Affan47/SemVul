dispose (GObject *object)
{
	NMFirewallManagerPrivate *priv = NM_FIREWALL_MANAGER_GET_PRIVATE (object);

	if (priv->disposed)
		goto out;
	priv->disposed = TRUE;

	if (priv->dbus_mgr) {
		if (priv->name_owner_id)
			g_signal_handler_disconnect (priv->dbus_mgr, priv->name_owner_id);
		g_object_unref (G_OBJECT (priv->dbus_mgr));
	}

	if (priv->proxy)
		g_object_unref (priv->proxy);

out:

	G_OBJECT_CLASS (nm_firewall_manager_parent_class)->dispose (object);
}
