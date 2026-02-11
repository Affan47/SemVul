_get_setting_priority (NMSetting *setting)
{
	GHashTableIter iter;
	SettingInfo *info;

	_ensure_registered ();

	g_hash_table_iter_init (&iter, registered_settings);
	while (g_hash_table_iter_next (&iter, NULL, (gpointer) &info)) {
		if (G_OBJECT_TYPE (setting) == info->type)
			return info->priority;
	}
	return G_MAXUINT32;
}
