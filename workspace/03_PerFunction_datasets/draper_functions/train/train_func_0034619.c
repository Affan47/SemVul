utils_get_setting_locale_string(GKeyFile *keyfile,
		const gchar *group, const gchar *key, const gchar *default_value)
{
	gchar *result = g_key_file_get_locale_string(keyfile, group, key, NULL, NULL);

	return NVL(result, g_strdup(default_value));
}
