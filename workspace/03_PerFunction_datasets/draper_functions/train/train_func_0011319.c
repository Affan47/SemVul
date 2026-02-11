nm_vpn_plugin_utils_read_vpn_details (int fd,
                                      GHashTable **out_data,
                                      GHashTable **out_secrets)
{
	GHashTable *data, *secrets;
	gboolean success = FALSE;
	char *key = NULL, *val = NULL;
	GString *line;
	gchar c;

	if (out_data)
		g_return_val_if_fail (*out_data == NULL, FALSE);
	if (out_secrets)
		g_return_val_if_fail (*out_secrets == NULL, FALSE);

	data = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	secrets = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, free_secret);

	line = g_string_new (NULL);


	while (1) {
		ssize_t nr;
		GHashTable *hash = NULL;

		errno = 0;
		nr = read (fd, &c, 1);
		if (nr == -1) {
			if (errno == EAGAIN) {
				g_usleep (100);
				continue;
			}
			break;
		}

		if (c != '\n') {
			g_string_append_c (line, c);
			continue;
		}


		if (strcmp (line->str, "DONE") == 0)
			break;


		if (strncmp (line->str, DATA_KEY_TAG, strlen (DATA_KEY_TAG)) == 0) {
			hash = data;
			key = g_strdup (line->str + strlen (DATA_KEY_TAG));
		} else if (strncmp (line->str, DATA_VAL_TAG, strlen (DATA_VAL_TAG)) == 0) {
			hash = data;
			val = g_strdup (line->str + strlen (DATA_VAL_TAG));
		} else if (strncmp (line->str, SECRET_KEY_TAG, strlen (SECRET_KEY_TAG)) == 0) {
			hash = secrets;
			key = g_strdup (line->str + strlen (SECRET_KEY_TAG));
		} else if (strncmp (line->str, SECRET_VAL_TAG, strlen (SECRET_VAL_TAG)) == 0) {
			hash = secrets;
			val = g_strdup (line->str + strlen (SECRET_VAL_TAG));
		}
		g_string_truncate (line, 0);

		if (key && val && hash) {
			g_hash_table_insert (hash, key, val);
			key = NULL;
			val = NULL;
			success = TRUE;
		}
	}

	if (success) {
		if (out_data)
			*out_data = data;
		else
			g_hash_table_destroy (data);

		if (out_secrets)
			*out_secrets = secrets;
		else
			g_hash_table_destroy (secrets);
	} else {
		g_hash_table_destroy (data);
		g_hash_table_destroy (secrets);
	}

	g_string_free (line, TRUE);
	return success;
}
