file_entry_changed (GtkWidget *entry, gpointer data)
{
	struct AcpiNotifierPage *page = (struct AcpiNotifierPage *)data;
	if (!page->warning_box)
		return;

	if (!check_impl(gtk_entry_get_text(GTK_ENTRY(entry))))
		show_error(page, gtk_entry_get_text(GTK_ENTRY(entry)));
	else
		show_error(page, NULL);
}
