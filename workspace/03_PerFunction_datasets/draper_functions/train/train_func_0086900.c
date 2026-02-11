nm_dhcp_manager_get_lease_config (NMDHCPManager *self,
                                  const char *iface,
                                  const char *uuid,
                                  gboolean ipv6)
{
	NMDHCPManagerPrivate *priv = NM_DHCP_MANAGER_GET_PRIVATE (self);

	g_return_val_if_fail (iface != NULL, NULL);
	g_return_val_if_fail (uuid != NULL, NULL);

	if (priv->get_lease_config_func)
		return priv->get_lease_config_func (iface, uuid, ipv6);
	return NULL;
}
