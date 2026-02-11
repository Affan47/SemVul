create_connection (CEPageMaster *master, NMConnection *connection)
{
	NMSetting *s_port;

	s_port = nm_connection_get_setting (connection, NM_TYPE_SETTING_BRIDGE_PORT);
	if (!s_port) {
		s_port = nm_setting_bridge_port_new ();
		nm_connection_add_setting (connection, s_port);
	}
}
