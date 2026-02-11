addrconf6_cleanup (NMDevice *self)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);

	if (priv->ac_ip6_config) {
		g_object_unref (priv->ac_ip6_config);
		priv->ac_ip6_config = NULL;
	}

	if (!priv->ip6_manager)
		return;

	if (priv->ip6_addrconf_sigid) {
		g_signal_handler_disconnect (priv->ip6_manager,
		                             priv->ip6_addrconf_sigid);
		priv->ip6_addrconf_sigid = 0;
	}
	if (priv->ip6_config_changed_sigid) {
		g_signal_handler_disconnect (priv->ip6_manager,
		                             priv->ip6_config_changed_sigid);
		priv->ip6_config_changed_sigid = 0;
	}

	nm_ip6_manager_cancel_addrconf (priv->ip6_manager, nm_device_get_ip_ifindex (self));
	g_object_unref (priv->ip6_manager);
	priv->ip6_manager = NULL;
}
