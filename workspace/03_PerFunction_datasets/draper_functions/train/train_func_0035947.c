read_one_setting (gpointer data, gpointer user_data)
{
	char *name;
	ReadFromGConfInfo *info = (ReadFromGConfInfo *) user_data;
	NMSetting *setting;


	name =  (char *) data + info->dir_len + 1;
	setting = nm_connection_create_setting (name);
	if (setting) {
		nm_setting_enumerate_values (setting,
							    read_one_setting_value_from_gconf,
							    info);
		nm_connection_add_setting (info->connection, setting);
	}

	g_free (data);
}
