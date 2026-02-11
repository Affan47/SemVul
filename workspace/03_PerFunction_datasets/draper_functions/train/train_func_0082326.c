set_blocked_entry(GtkWidget *entry, const gchar *str, guint sig)
{
	if(sig > 0)
		g_signal_handler_block(G_OBJECT(entry), sig);

	if(str != NULL)
		gtk_entry_set_text(GTK_ENTRY(entry), str);
	else
		gtk_entry_set_text(GTK_ENTRY(entry), "");

	if(sig > 0)
		g_signal_handler_unblock(G_OBJECT(entry), sig);
}
