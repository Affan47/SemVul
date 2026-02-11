get_modify_permission_basic (NMSettingsConnection *connection)
{
	NMSettingConnection *s_con;


	s_con = nm_connection_get_setting_connection (NM_CONNECTION (connection));
	g_assert (s_con);
	if (nm_setting_connection_get_num_permissions (s_con) == 1)
		return NM_AUTH_PERMISSION_SETTINGS_MODIFY_OWN;

	return NM_AUTH_PERMISSION_SETTINGS_MODIFY_SYSTEM;
}
