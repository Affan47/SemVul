ip6_start (NMDHCPClient *client,
           NMSettingIP6Config *s_ip6,
           guint8 *dhcp_anycast_addr,
           const char *hostname,
           gboolean info_only,
           const GByteArray *duid)
{
	NMDHCPDhclientPrivate *priv = NM_DHCP_DHCLIENT_GET_PRIVATE (client);
	const char *iface;

	iface = nm_dhcp_client_get_iface (client);

	priv->conf_file = create_dhclient_config (iface, TRUE, NULL, s_ip6, dhcp_anycast_addr, hostname);
	if (!priv->conf_file) {
		nm_log_warn (LOGD_DHCP6, "(%s): error creating dhclient6 configuration file.", iface);
		return -1;
	}

	return dhclient_start (client, info_only ? "-S" : "-N", duid, FALSE);
}
