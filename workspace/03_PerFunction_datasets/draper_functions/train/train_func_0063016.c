pl3_current_playlist_connection_changed(GmpcConnection * conn, MpdObj * mi, int connect,
													PlayQueuePlugin * self)
{
	if (!connect && self->priv->filter_entry)
	{
		gtk_entry_set_text(GTK_ENTRY(self->priv->filter_entry), "");
	}
}
