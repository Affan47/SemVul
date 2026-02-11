server_unregister(struct btd_adapter *adapter)
{
	struct network_adapter *na;
	struct network_server *ns;
	uint16_t id = BNEP_SVC_NAP;

	na = find_adapter(adapters, adapter);
	if (!na)
		return -EINVAL;

	ns = find_server(na->servers, id);
	if (!ns)
		return -EINVAL;

	g_dbus_unregister_interface(connection, adapter_get_path(adapter),
					ns->iface);

	return 0;
}
