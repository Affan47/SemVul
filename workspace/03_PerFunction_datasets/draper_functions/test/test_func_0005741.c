on_ok (GtkWidget *widget)
{
	mailbox_->username (gtk_entry_get_text (GTK_ENTRY (get("username_entry"))));
	mailbox_->password (gtk_entry_get_text (GTK_ENTRY (get("password_entry"))));
	hide();
	g_mutex_unlock (access_mutex_);
	gtk_main_quit ();
}
