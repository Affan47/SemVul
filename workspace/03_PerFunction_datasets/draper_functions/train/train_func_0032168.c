system_timezone_read_key_file (const gchar *filename,
                               const gchar *key)
{
	GIOChannel *channel;
	gchar       *key_eq;
	gchar       *line;
	gchar       *retval;

	if (!g_file_test (filename, G_FILE_TEST_IS_REGULAR))
		return NULL;

	channel = g_io_channel_new_file (filename, "r", NULL);
	if (!channel)
		return NULL;

	key_eq = g_strdup_printf ("%s=", key);
	retval = NULL;

	while (g_io_channel_read_line (channel, &line, NULL,
				       NULL, NULL) == G_IO_STATUS_NORMAL) {
		if (g_str_has_prefix (line, key_eq)) {
			gchar *value;
			gint   len;

			value = line + strlen (key_eq);
			g_strstrip (value);

			len = strlen (value);

			if (value[0] == '\"' && value[len - 1] == '\"') {
				value += 1;
				len -= 2;
			}

			g_free (retval);
			retval = g_strndup (value, len);
			g_strstrip (retval);
		}

		g_free (line);
	}

	g_free (key_eq);
	g_io_channel_unref (channel);

	return retval;
}
