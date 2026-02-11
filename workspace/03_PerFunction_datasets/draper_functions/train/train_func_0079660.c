stop (NMDHCPClient *self, gboolean release, const GByteArray *duid)
{
	NMDHCPClientPrivate *priv;

	g_return_if_fail (self != NULL);
	g_return_if_fail (NM_IS_DHCP_CLIENT (self));

	priv = NM_DHCP_CLIENT_GET_PRIVATE (self);
	g_return_if_fail (priv->pid > 0);


	watch_cleanup (self);

	nm_dhcp_client_stop_pid (priv->pid, priv->iface, 0);

	priv->info_only = FALSE;
}
