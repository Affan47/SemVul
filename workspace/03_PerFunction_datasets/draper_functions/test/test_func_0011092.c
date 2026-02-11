gyrus_session_set_defaults_from_session (GyrusSession *session)
{
	gint value = 0;

	g_return_if_fail (session);

	gtk_entry_set_text (GTK_ENTRY (entry_host), session->host);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton_port), (gdouble) session->port);
	gtk_entry_set_text (GTK_ENTRY (entry_user), session->user);
	gtk_entry_set_text (GTK_ENTRY (entry_name), session->name);

	if (strcmp (session->sep_char, ".") == 0)
		value = 0;
	else if (strcmp (session->sep_char, "/") == 0)
		value = 1;
	else if (strcmp (session->sep_char, "auto") == 0)
		value = 2;

	gtk_combo_box_set_active (GTK_COMBO_BOX (combobox_sep_char),
				  value);

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton_secure),
	                              session->usetls);
}
