nlh_setup (struct nl_sock *nlh,
           nl_recvmsg_msg_cb_t valid_func,
           gpointer cb_data,
           GError **error)
{
	int err;

	nl_socket_modify_cb (nlh, NL_CB_MSG_IN, NL_CB_CUSTOM, event_msg_recv, NULL);

	if (valid_func)
		nl_socket_modify_cb (nlh, NL_CB_VALID, NL_CB_CUSTOM, valid_func, cb_data);

	err = nl_connect (nlh, NETLINK_ROUTE);
	if (err < 0) {
		g_set_error (error, NM_NETLINK_MONITOR_ERROR,
		             NM_NETLINK_MONITOR_ERROR_NETLINK_CONNECT,
		             _("unable to connect to netlink for monitoring link status: %s"),
		             nl_geterror (err));
		return FALSE;
	}


	if (nl_socket_set_passcred (nlh, 1) < 0) {
		g_set_error (error, NM_NETLINK_MONITOR_ERROR,
		             NM_NETLINK_MONITOR_ERROR_NETLINK_CONNECT,
		             _("unable to enable netlink handle credential passing: %s"),
		             nl_geterror (err));
		return FALSE;
	}

	return TRUE;
}
