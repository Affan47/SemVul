ensure_loaded (void)
{
	GKeyFile *keyfile;
	gchar *str, **keys;
	gint i;

	if (key2fmt)
		return;

	key2fmt = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	keyfile = g_key_file_new ();

	str = g_build_filename (e_get_user_data_dir (), KEYS_FILENAME, NULL);
	g_key_file_load_from_file (keyfile, str, G_KEY_FILE_NONE, NULL);
	g_free (str);

	keys = g_key_file_get_keys (keyfile, KEYS_GROUPNAME, NULL, NULL);

	if (keys) {
		for (i = 0;  keys[i]; i++) {
			str = g_key_file_get_string (keyfile, KEYS_GROUPNAME, keys[i], NULL);
			if (str)
				g_hash_table_insert (key2fmt, g_strdup (keys[i]), str);
		}

		g_strfreev (keys);
	}

	g_key_file_free (keyfile);
}
