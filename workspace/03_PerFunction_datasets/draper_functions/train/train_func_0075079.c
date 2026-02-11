update_position()
{
	GtkLabel *label_msg;
	label_msg = (GtkLabel *)lookup_widget(window1, "label51");
	gtk_label_set_label (label_msg, _("Connecting..."));

	if (!g_thread_create(&update_position_thread, NULL, FALSE, NULL) != 0)
		g_warning("### can't create friend thread\n");

	return TRUE;
}
