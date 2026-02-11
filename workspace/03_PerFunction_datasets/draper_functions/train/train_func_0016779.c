nm_netlink_foreach_route (int ifindex,
                          int family,
                          int scope,
                          gboolean ignore_inet6_ll_mc,
                          NlRouteForeachFunc callback,
                          gpointer user_data)
{
	struct nl_cache *cache;
	ForeachRouteInfo info;

	memset (&info, 0, sizeof (info));
	info.ifindex = ifindex;
	info.family = family;
	info.scope = scope;
	info.ignore_inet6_ll_mc = ignore_inet6_ll_mc;
	info.callback = callback;
	info.user_data = user_data;
	info.iface = nm_netlink_index_to_iface (ifindex);

	rtnl_route_alloc_cache (nm_netlink_get_default_handle (), family, 0, &cache);
	g_warn_if_fail (cache != NULL);
	if (cache) {
		nl_cache_foreach (cache, foreach_route_cb, &info);
		nl_cache_free (cache);
	}
	g_free (info.iface);
	return info.out_route;
}
