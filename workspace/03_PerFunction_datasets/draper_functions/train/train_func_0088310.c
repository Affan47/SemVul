get_combobox_text(GtkWidget* combo)
{
	UT_UCS4String ucs = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo))));

	return ucs;
}
