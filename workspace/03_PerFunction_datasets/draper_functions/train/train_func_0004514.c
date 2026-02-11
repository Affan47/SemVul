on_entry_repository_user_email_focus_out_event (GtkEntry *entry,
                                                GdkEventFocus *focus,
                                                GitgRepositoryDialog *dialog)
{
	gchar const *text;

	text = gtk_entry_get_text (entry);
	gitg_config_set_value (dialog->priv->config, "user.email", *text ? text : NULL);

	return FALSE;
}
