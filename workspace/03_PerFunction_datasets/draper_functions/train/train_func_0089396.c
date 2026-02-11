handle_strv_setting(StashGroup *group, StashPref *se,
		GKeyFile *config, SettingAction action)
{
	gchararray **setting = se->setting;

	switch (action)
	{
		case SETTING_READ:
			g_strfreev(*setting);
			*setting = g_key_file_get_string_list(config, group->name, se->key_name,
				NULL, NULL);
			if (*setting == NULL)
				*setting = g_strdupv(se->default_value);
			break;

		case SETTING_WRITE:
		{

			const gchar *dummy[] = { "", NULL };
			const gchar **strv = *setting ? (const gchar **)*setting : dummy;

			g_key_file_set_string_list(config, group->name, se->key_name,
				strv, g_strv_length((gchar **)strv));
			break;
		}
	}
}
