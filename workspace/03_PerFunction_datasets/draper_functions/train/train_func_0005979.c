gyrus_admin_mailbox_on_button_quota_apply_clicked (GtkButton *button,
						   gpointer userdata)
{
	GyrusAdmin * admin = GYRUS_ADMIN (userdata);
	gchar **tokens;
	const gchar *new_quota_str;
	gint new_quota;
	gchar *new_quota_invalid;
	gchar *mailbox_path;

	new_quota_str =
		gtk_entry_get_text (GTK_ENTRY (admin->priv->entry_quota_new));

	if (!g_ascii_strcasecmp (new_quota_str, ""))
		return;

	mailbox_path = g_strdup (gtk_label_get_text
				 (GTK_LABEL (admin->priv->label_mailbox_name)));

	new_quota = 1024 * g_strtod (new_quota_str, &new_quota_invalid);

	if (*new_quota_invalid) {
		gyrus_common_show_message (NULL, GTK_MESSAGE_ERROR,
					   _("Quota not valid. Please try again."));
		g_free (mailbox_path);
		return;
	}

	if (gyrus_admin_mailbox_set_quota (admin, mailbox_path, new_quota)) {
		gtk_entry_set_text (GTK_ENTRY (admin->priv->entry_quota_new),
				    "");
		tokens = g_strsplit (mailbox_path, gyrus_admin_get_separator_char (admin), 3);
		gyrus_admin_mailbox_show_info (admin, tokens[1], mailbox_path);
		g_strfreev (tokens);
	}
	else
		gyrus_common_show_message (NULL, GTK_MESSAGE_ERROR,
					   _("Unable to change quota. "
					     "Are you sure do you have the appropriate permissions?"));

	g_free (mailbox_path);

}
