evt_clickmclick_pick_clicked(GtkWidget *wid, gpointer user)
{
	P_Controls	*page = user;

	if(page)
	{
		const gchar	*cmd = csq_dialog_sync_new_wait(page->min, ccs_get_current());
		if(cmd)
			gtk_entry_set_text(GTK_ENTRY(page->cmccmd), cmd);
	}
}
