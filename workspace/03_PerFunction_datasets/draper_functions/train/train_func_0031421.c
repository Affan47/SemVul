filter_input_get_widget (EFilterElement *element)
{
	EFilterInput *input = E_FILTER_INPUT (element);
	GtkWidget *entry;

	entry = gtk_entry_new ();
	if (input->values && input->values->data)
		gtk_entry_set_text (
			GTK_ENTRY (entry), input->values->data);

	g_signal_connect (
		entry, "changed",
		G_CALLBACK (filter_input_entry_changed), element);

	return entry;
}
