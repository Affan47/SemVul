nm_ip6_config_to_rtnl_addr (NMIP6Config *config, guint32 i, guint32 flags)
{
	NMIP6ConfigPrivate *priv = NM_IP6_CONFIG_GET_PRIVATE (config);
	NMIP6Address *config_addr;
	struct rtnl_addr *addr;
	gboolean success = TRUE;

	g_return_val_if_fail (NM_IS_IP6_CONFIG (config), NULL);

	config_addr = nm_ip6_config_get_address (config, i);
	g_return_val_if_fail (config_addr != NULL, NULL);

	if (!(addr = rtnl_addr_alloc()))
		return NULL;

	if (flags & NM_RTNL_ADDR_ADDR) {
		success = (ip6_addr_to_rtnl_local (nm_ip6_address_get_address (config_addr),
		                                   addr,
		                                   nm_ip6_address_get_prefix (config_addr)) >= 0);
	}

	if (flags & NM_RTNL_ADDR_PTP_ADDR)
		success = (ip6_addr_to_rtnl_peer (&priv->ptp_address, addr) >= 0);

	if (flags & NM_RTNL_ADDR_PREFIX)
		rtnl_addr_set_prefixlen (addr, nm_ip6_address_get_prefix (config_addr));

	if (!success) {
		rtnl_addr_put (addr);
		addr = NULL;
	}

	return addr;
}
