_gth_browser_update_paste_command_sensitivity (GthBrowser   *browser,
                                               GtkClipboard *clipboard)
{
	BrowserData *data;

	data = g_object_get_data (G_OBJECT (browser), BROWSER_DATA_KEY);
	g_return_if_fail (data != NULL);

	data->can_paste = FALSE;
        set_action_sensitive (data, "Edit_PasteInFolder", FALSE);

	if (clipboard == NULL)
		clipboard = gtk_widget_get_clipboard (GTK_WIDGET (browser), GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_request_targets (clipboard,
				       clipboard_targets_received_cb,
				       g_object_ref (browser));
}
