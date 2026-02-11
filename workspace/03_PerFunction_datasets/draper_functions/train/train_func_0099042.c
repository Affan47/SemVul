evt_baf_rescan_clicked(GtkWidget *wid, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdRow		*row;
	guint32		mask = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(wid), "user"));

	if(!get_selections(page, NULL, &row))
		return;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)))
		row->extra.external.baflags[1] |= mask;
	else
		row->extra.external.baflags[1] &= ~mask;
}
