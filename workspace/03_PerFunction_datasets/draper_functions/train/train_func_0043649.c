evt_cmdseq_pick_clicked(GtkWidget *wid, gpointer user)
{
	P_Buttons	*page = user;
	Button		*btn;

	if((page != NULL) && ((btn = btn_button_get(page->button)) != NULL))
	{
		BtnFace		face;
		const gchar	*csq;

		face = (BtnFace) GPOINTER_TO_UINT(g_object_get_data(G_OBJECT(wid), "face"));
		if((csq = csq_dialog_sync_new_wait(page->min, ccs_get_current())) != NULL)
			gtk_entry_set_text(GTK_ENTRY(page->def[face].cmdseq), csq);
	}
}
