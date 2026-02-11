_get_type_setting (NMConnection *connection)
{
	NMSettingConnection *s_con;
	const char *type;
	NMSetting *base;

	g_return_val_if_fail (NM_IS_CONNECTION (connection), NULL);

	s_con = nm_connection_get_setting_connection (connection);
	g_assert (s_con);

	type = nm_setting_connection_get_connection_type (s_con);
	g_assert (type);

	base = nm_connection_get_setting_by_name (connection, type);
	g_assert (base);

	return base;
}
