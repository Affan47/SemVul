gth_browser_activate_action_edit_paste (GtkAction  *action,
					GthBrowser *browser)
{
	GtkWidget *focused_widget;
	PasteData *paste_data;

	focused_widget = gtk_window_get_focus (GTK_WINDOW (browser));
	if ((focused_widget != NULL) && GTK_IS_EDITABLE (focused_widget))
		return;

	paste_data = g_new0 (PasteData, 1);
	paste_data->browser = g_object_ref (browser);
	paste_data->destination = g_object_ref (gth_browser_get_location_data (browser));

	gtk_clipboard_request_contents (gtk_widget_get_clipboard (GTK_WIDGET (browser), GDK_SELECTION_CLIPBOARD),
					GNOME_COPIED_FILES,
					clipboard_received_cb,
					paste_data);
}
