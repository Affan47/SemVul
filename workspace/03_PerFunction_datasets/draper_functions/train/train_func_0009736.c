notify_save_command(PrefsPage *page)
{
	gdouble timeout;
	const gchar *tmp_str;

	notify_config.command_enabled =
	gtk_toggle_button_get_active
	(GTK_TOGGLE_BUTTON(command_page.command_enabled));

	timeout =
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(command_page.command_timeout));
	notify_config.command_timeout = (gint)floor(timeout*1000+0.5);
	notify_config.command_folder_specific =
	gtk_toggle_button_get_active
	(GTK_TOGGLE_BUTTON(command_page.command_folder_specific));

	tmp_str = gtk_entry_get_text(GTK_ENTRY(command_page.command_line));
	if(notify_config.command_line)
      g_free(notify_config.command_line);
	notify_config.command_line = g_strdup(tmp_str);
}
