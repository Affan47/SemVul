gyrus_admin_mailbox_get_quota (GyrusAdmin *admin, const gchar *mailbox_path,
			       gint *quota_limit, gint *quota_used,
			       gchar **error)
{
	gchar *msg, **parts;
	GyrusImapStatus status;

	msg = g_strdup_printf (". getquota \"%s\"\n", mailbox_path);
	gyrus_admin_write_channel (admin, msg);
	g_free (msg);

	*error = NULL;

	status = gyrus_admin_listen_channel (admin, &msg, NULL);
	if (status == GYRUS_IMAP_STATUS_BYE) {
		g_free (msg);
		return FALSE;
	}

	parts = g_strsplit (msg, " ", -1);
	if (g_ascii_strcasecmp (parts[1], "QUOTA") == 0) {
		g_strfreev (parts);
		parts = g_strsplit (msg, "(", -1);
		sscanf (parts[1], "STORAGE %d %d)",
			quota_used, quota_limit);
		g_free (msg);
		gyrus_admin_listen_channel (admin, &msg, NULL);
	}
	else if (g_ascii_strcasecmp (parts[1], "NO") == 0) {
		*quota_used = -1;
		*quota_limit = -1;
		if (strcmp (parts [2], "Quota") == 0)
			*error = g_strdup (_("Quota does not exist"));
		else if (strcmp (parts [2], "Permission") == 0)
			*error = g_strdup (_("Permission denied"));
	}
	g_free (msg);
	g_strfreev (parts);
	return TRUE;
}
