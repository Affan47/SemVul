wifi_utils_set_mesh_channel (WifiData *data, guint32 channel)
{
	g_return_val_if_fail (data != NULL, FALSE);
	g_return_val_if_fail (channel >= 0, FALSE);
	g_return_val_if_fail (channel <= 13, FALSE);
	g_return_val_if_fail (data->set_mesh_channel != NULL, FALSE);
	return data->set_mesh_channel (data, channel);
}
