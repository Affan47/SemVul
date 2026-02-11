apply_window_add_tag_cb(GtkWidget *widget,
			         gpointer data)
{
	if (applywindow.busy)
		return;
	apply_window_add_tag();
	gtk_entry_set_text(GTK_ENTRY(applywindow.add_entry), "");
	gtk_widget_grab_focus(applywindow.taglist);
}
