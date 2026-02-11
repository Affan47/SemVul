nm_netlink_route_delete (struct rtnl_route *route)
{
	struct nl_sock *nlh;
	int err = 0;

	g_return_val_if_fail (route != NULL, FALSE);

	nlh = nm_netlink_get_default_handle ();
	err = rtnl_route_delete (nlh, route, 0);

	if (err)
		nm_log_dbg (LOGD_IP4 | LOGD_IP6, "%s (%d)", nl_geterror(err), err);


	if (err == -NLE_FAILURE)
		err = -NLE_OBJ_NOTFOUND;

	return (err && (err != -NLE_OBJ_NOTFOUND) && (err != -NLE_RANGE) ) ? FALSE : TRUE;
}
