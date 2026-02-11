dlg_dialog_track_entry(Dialog *dlg, GtkWidget *entry)
{
	if(dlg == NULL)
		return;
	g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(evt_entry_changed), dlg);

	evt_entry_changed(entry, dlg);
}
