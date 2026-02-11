dialog_password_entry_changed_cb (GtkEditable *password_entry, gpointer user_data)
{
	GtkWidget * button = GTK_WIDGET(g_object_get_data (G_OBJECT(password_entry), "ok_button"));
	guint minimum_length = GPOINTER_TO_INT (g_object_get_data (G_OBJECT(password_entry),
                                                                   "minimum_length"));

	if (strlen (gtk_entry_get_text (GTK_ENTRY(password_entry))) >= minimum_length)
		gtk_widget_set_sensitive (button, TRUE);
	else
		gtk_widget_set_sensitive (button, FALSE);

}
