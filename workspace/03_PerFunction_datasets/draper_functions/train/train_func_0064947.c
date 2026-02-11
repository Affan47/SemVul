nm_system_iface_set_mac (int ifindex, const struct ether_addr *mac)
{
	struct rtnl_link *old, *new;
	gboolean success = FALSE;
	struct nl_sock *nlh;
	char *iface;
	struct nl_addr *addr = NULL;
	int err;

	g_return_val_if_fail (ifindex > 0, FALSE);
	g_return_val_if_fail (mac != NULL, FALSE);

	new = rtnl_link_alloc ();
	if (!new)
		return FALSE;

	iface = nm_netlink_index_to_iface (ifindex);
	if (!iface)
		goto out;

	old = nm_netlink_index_to_rtnl_link (ifindex);
	if (old) {
		addr = nl_addr_build (AF_LLC, (void *) mac, ETH_ALEN);
		if (!addr) {
			nm_log_err (LOGD_HW, "(%s): failed to allocate memory for MAC address change", iface);
			rtnl_link_put (old);
			rtnl_link_put (new);
			return FALSE;
		}
		rtnl_link_set_addr (new, addr);
		nl_addr_put (addr);
		nlh = nm_netlink_get_default_handle ();
		if (nlh) {
			err = rtnl_link_change (nlh, old, new, 0);
			if (err == 0)
				success = TRUE;
			else
				nm_log_warn (LOGD_HW, "(%s): failed to change interface MAC address", iface);
		}
		rtnl_link_put (old);
	}

out:
	rtnl_link_put (new);
	g_free (iface);
	return success;
}
