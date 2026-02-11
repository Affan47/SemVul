gyrus_session_new_from_interface (void)
{
	GyrusSession *session = g_new (GyrusSession, 1);

	if (g_utf8_strlen (gtk_entry_get_text (GTK_ENTRY (entry_host)), -1))
		session->host = g_strdup (gtk_entry_get_text (GTK_ENTRY (entry_host)));
	else
		session->host = NULL;

	session->port = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON
							  (spinbutton_port));

	if (g_utf8_strlen (gtk_entry_get_text (GTK_ENTRY (entry_user)), -1))
		session->user = g_strdup (gtk_entry_get_text (GTK_ENTRY (entry_user)));
	else
		session->user = NULL;

	if (g_utf8_strlen (gtk_entry_get_text (GTK_ENTRY (entry_name)), -1))
		session->name = g_strdup (gtk_entry_get_text (GTK_ENTRY (entry_name)));
	else
		session->name = NULL;

	if (g_utf8_strlen (gtk_entry_get_text (GTK_ENTRY (entry_passwd)), -1))
		session->passwd = g_strdup (gtk_entry_get_text (GTK_ENTRY (entry_passwd)));
	else
		session->passwd = NULL;

	session->sep_char = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox_sep_char));
	if (!g_utf8_strlen (session->sep_char, -1))
		session->sep_char = g_strdup (".");
	else if (strcmp (session->sep_char, _("Autodetect")) == 0) {
		g_free (session->sep_char);
		session->sep_char = g_strdup ("auto");
	}

	session->usetls = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_secure));

	return session;
}
