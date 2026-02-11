on_new_ca_pwd_entry_changed (GtkEntry *entry,
				       gpointer user_data)
{
	const gchar *text1;
	const gchar *text2;

	GtkEntry *pwd_entry_1 = GTK_ENTRY(gtk_builder_get_object (new_ca_window_gtkb, "new_ca_pwd_entry_1"));
	GtkEntry *pwd_entry_2 = GTK_ENTRY(gtk_builder_get_object (new_ca_window_gtkb, "new_ca_pwd_entry_2"));
	GtkButton *commit_button = GTK_BUTTON(gtk_builder_get_object (new_ca_window_gtkb, "new_ca_commit"));

	text1 = gtk_entry_get_text (pwd_entry_1);
	text2 = gtk_entry_get_text (pwd_entry_2);

	if (strlen(text1) && strlen(text2) && ! strcmp(text1, text2)) {
		gtk_widget_set_sensitive (GTK_WIDGET(commit_button), TRUE);
	} else {
		gtk_widget_set_sensitive (GTK_WIDGET(commit_button), FALSE);
	}

}
