gyrus_admin_listen_channel (GyrusAdmin *admin, gchar **message, gint *msg_len)
{
	gsize bytes_read;
	gchar **tokens = NULL;
	GyrusImapStatus imap_status;

	*message = NULL;


	do {
		g_free (*message);
		g_strfreev (tokens);

		imap_status = GYRUS_IMAP_STATUS_OK;
		*message = socket_readline (admin, &bytes_read);

#ifdef DEBUG_PLAIN_CHANNEL
		g_print ("read:  %s", *message);
#endif
		tokens = g_strsplit (*message, " ", 0);
		if (msg_len != NULL)
			*msg_len = bytes_read;


		if (g_ascii_strcasecmp (tokens [2], "[ALERT]") == 0) {
			gyrus_common_show_message (NULL, GTK_MESSAGE_INFO,
						   *message + strlen ("* OK "));

		}
	} while (g_ascii_strcasecmp (tokens [2], "[ALERT]") == 0);

	if (g_ascii_strcasecmp (tokens[1], "BYE") == 0)
		imap_status = GYRUS_IMAP_STATUS_BYE;
	else if (g_ascii_strcasecmp (tokens[1], "OK") == 0)
		imap_status = GYRUS_IMAP_STATUS_OK;
	else if (g_ascii_strcasecmp (tokens[1], "BAD") == 0)
		imap_status = GYRUS_IMAP_STATUS_BAD;
	else if (g_ascii_strcasecmp (tokens[1], "NO") == 0)
		imap_status = GYRUS_IMAP_STATUS_NO;
	else if (g_ascii_strcasecmp (tokens [1], "LIST") == 0)
		imap_status = GYRUS_IMAP_STATUS_LIST;

	g_strfreev (tokens);

	return imap_status;
}
