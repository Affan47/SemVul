pl3_current_playlist_status_changed(GmpcConnection * conn, MpdObj * mi, ChangedStatusType what,
												PlayQueuePlugin * self)
{
	if (self->priv->pl3_cp_vbox == NULL)
		return;
	if (what & MPD_CST_PLAYLIST)
	{

		if (self->priv->quick_search)
			mod_fill_do_entry_changed(self);
	}
}
