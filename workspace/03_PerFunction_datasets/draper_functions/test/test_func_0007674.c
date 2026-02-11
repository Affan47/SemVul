set_smb_name (const gchar *name)
{
	GtkWidget *entry;
	gboolean modified;

	entry = gst_dialog_get_widget (tool->main_dialog, "share_smb_name");

	modified = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (entry), "modified"));

	if (!modified) {
		g_signal_handlers_block_by_func (entry, on_share_smb_name_modified, tool->main_dialog);
		gtk_entry_set_text (GTK_ENTRY (entry), name);
		g_signal_handlers_unblock_by_func (entry, on_share_smb_name_modified, tool->main_dialog);
	}
}
