nm_ip6_config_take_address (NMIP6Config *config, NMIP6Address *address)
{
	NMIP6ConfigPrivate *priv;

	g_return_if_fail (NM_IS_IP6_CONFIG (config));
	g_return_if_fail (address != NULL);

	priv = NM_IP6_CONFIG_GET_PRIVATE (config);
	priv->addresses = g_slist_append (priv->addresses, address);
}
