brasero_setting_get_integer (GKeyFile *file,
                             const gchar *group_name,
                             const gchar *key)
{
	GError *error = NULL;
	gint int_value;

	int_value = g_key_file_get_integer (file, group_name, key, &error);
	if (!int_value && error) {
		g_error_free (error);
		return -1;
	}

	return int_value;
}
