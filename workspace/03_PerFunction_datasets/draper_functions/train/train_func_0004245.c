inet_connection_succeeded(const host_addr_t addr)
{


	if (is_local_addr(addr))
		return;

	if (
		wd_sleep(outgoing_wd) &&
		!GNET_PROPERTY(is_inet_connected) &&
		GNET_PROPERTY(fw_debug)
	) {
		g_debug("FW: outgoing TCP connection succeeded => connected");
	}

	if (!GNET_PROPERTY(is_inet_connected))
		inet_set_is_connected(TRUE);
}
