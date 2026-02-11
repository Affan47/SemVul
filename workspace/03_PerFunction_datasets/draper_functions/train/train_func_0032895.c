prefs_account_signature_edit_cb(GtkWidget *widget, gpointer data)
{
	const gchar *sigpath = gtk_entry_get_text(GTK_ENTRY(data));
	if (!is_file_exist(sigpath))
		str_write_to_file(sigpath, "");
	open_txt_editor(sigpath, prefs_common_get_ext_editor_cmd());
}
