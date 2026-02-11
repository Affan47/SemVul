nm_supplicant_manager_iface_release (NMSupplicantManager *self,
                                     NMSupplicantInterface *iface)
{
	NMSupplicantManagerPrivate *priv;
	const char *ifname, *op;

	g_return_if_fail (NM_IS_SUPPLICANT_MANAGER (self));
	g_return_if_fail (NM_IS_SUPPLICANT_INTERFACE (iface));

	ifname = nm_supplicant_interface_get_ifname (iface);
	g_assert (ifname);

	priv = NM_SUPPLICANT_MANAGER_GET_PRIVATE (self);

	g_return_if_fail (g_hash_table_lookup (priv->ifaces, ifname) == iface);


	op = nm_supplicant_interface_get_object_path (iface);
	if (priv->running && priv->proxy && op) {
		dbus_g_proxy_call_no_reply (priv->proxy, "RemoveInterface",
			                        DBUS_TYPE_G_OBJECT_PATH, op,
			                        G_TYPE_INVALID);
	}

	g_hash_table_remove (priv->ifaces, ifname);
}
