nm_system_bond_release (gint master_ifindex,
                        const char *master_iface,
                        gint slave_ifindex,
                        const char *slave_iface)
{
	struct nl_sock *sock;
	int err;

	g_return_val_if_fail (master_ifindex > 0, FALSE);
	g_return_val_if_fail (master_iface != NULL, FALSE);
	g_return_val_if_fail (slave_ifindex > 0, FALSE);
	g_return_val_if_fail (slave_iface != NULL, FALSE);

	sock = nm_netlink_get_default_handle ();


	if (!(nm_system_iface_get_flags (slave_ifindex) & IFF_SLAVE))
		return TRUE;

	err = rtnl_link_bond_release_ifindex (sock, slave_ifindex);
	if (err == -NLE_OPNOTSUPP)
		return nm_system_bond_compat_release (master_iface, slave_iface);
	else if (err < 0) {
		nm_log_err (LOGD_DEVICE, "(%s): error releasing slave %s: %d (%s)",
		            master_iface, slave_iface, err, nl_geterror (err));
		return FALSE;
	}

	return TRUE;
}
