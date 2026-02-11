ssid_writer (GKeyFile *file,
             const char *keyfile_dir,
             const char *uuid,
             NMSetting *setting,
             const char *key,
             const GValue *value)
{
	GByteArray *array;
	const char *setting_name = nm_setting_get_name (setting);
	gboolean new_format = TRUE;
	unsigned int semicolons = 0;
	int i, *tmp_array;
	char *ssid;

	g_return_if_fail (G_VALUE_HOLDS (value, DBUS_TYPE_G_UCHAR_ARRAY));

	array = (GByteArray *) g_value_get_boxed (value);
	if (!array || !array->len)
		return;


	for (i = 0; i < array->len; i++) {
		char c = array->data[i] & 0xFF;
		if (!g_ascii_isprint (c)) {
			new_format = FALSE;
			break;
		}
		if (c == ';')
			semicolons++;
	}

	if (new_format) {
		ssid = g_malloc0 (array->len + semicolons + 1);
		if (semicolons == 0)
			memcpy (ssid, array->data, array->len);
		else {


			int j = 0;
			for (i = 0; i < array->len; i++) {
				if (array->data[i] == ';')
					ssid[j++] = '\\';
				ssid[j++] = array->data[i];
			}
		}
		g_key_file_set_string (file, setting_name, key, ssid);
		g_free (ssid);
	} else {
		tmp_array = g_new (gint, array->len);
		for (i = 0; i < array->len; i++)
			tmp_array[i] = (int) array->data[i];
		g_key_file_set_integer_list (file, setting_name, key, tmp_array, array->len);
		g_free (tmp_array);
	}
}
