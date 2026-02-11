vpn_type_result_func (NMConnection *connection, gpointer user_data)
{
	NewVpnInfo *info = user_data;

	info->result_func (connection, connection == NULL, NULL, info->user_data);
	g_slice_free (NewVpnInfo, info);
}
