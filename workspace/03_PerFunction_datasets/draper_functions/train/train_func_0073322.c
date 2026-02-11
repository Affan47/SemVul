gth_browser_save_state (GthBrowser *browser)
{
	browser_state_free (&browser->priv->state);

	browser->priv->state.saved = TRUE;
	browser->priv->state.page = gth_window_get_current_page (GTH_WINDOW (browser));
	if (browser->priv->location != NULL)
		browser->priv->state.location = g_object_ref (browser->priv->location->file);
	if (browser->priv->current_file != NULL)
		browser->priv->state.current_file = g_object_ref (browser->priv->current_file->file);
	browser->priv->state.selected = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_file_list_get_view (GTH_FILE_LIST (browser->priv->file_list))));
	browser->priv->state.vscroll = gtk_adjustment_get_value (gth_file_list_get_vadjustment (GTH_FILE_LIST (browser->priv->file_list)));
}
