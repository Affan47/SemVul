evt_sync_key_pressed(GtkWidget *wid, GdkEventKey *evt, gpointer user)
{
	Dialog	*dlg = user;

	if(evt->keyval == GDK_Escape)
		gtk_dialog_response(GTK_DIALOG(dlg->dlg), dlg->last_button);
	else
		return FALSE;
	return TRUE;
}
