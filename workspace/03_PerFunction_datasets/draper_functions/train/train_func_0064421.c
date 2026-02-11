nm_ip6_manager_init (NMIP6Manager *manager)
{
	NMIP6ManagerPrivate *priv = NM_IP6_MANAGER_GET_PRIVATE (manager);

	priv->devices = g_hash_table_new_full (g_direct_hash, g_direct_equal,
	                                       NULL,
	                                       (GDestroyNotify) nm_ip6_device_destroy);

	priv->monitor = nm_netlink_monitor_get ();
	nm_netlink_monitor_subscribe (priv->monitor, RTNLGRP_IPV6_IFADDR, NULL);
	nm_netlink_monitor_subscribe (priv->monitor, RTNLGRP_IPV6_PREFIX, NULL);
	nm_netlink_monitor_subscribe (priv->monitor, RTNLGRP_IPV6_ROUTE, NULL);
	nm_netlink_monitor_subscribe (priv->monitor, RTNLGRP_ND_USEROPT, NULL);
	nm_netlink_monitor_subscribe (priv->monitor, RTNLGRP_LINK, NULL);

	priv->netlink_id = g_signal_connect (priv->monitor, "notification",
	                                     G_CALLBACK (netlink_notification), manager);

	priv->nlh = nm_netlink_get_default_handle ();
	rtnl_addr_alloc_cache (priv->nlh, &priv->addr_cache);
	g_warn_if_fail (priv->addr_cache != NULL);
	rtnl_route_alloc_cache (priv->nlh, NETLINK_ROUTE, NL_AUTO_PROVIDE, &priv->route_cache);
	g_warn_if_fail (priv->route_cache != NULL);
}
