set_current_page__file_saved_cb (GthBrowser *browser,
				 gboolean    cancelled,
				 gpointer    user_data)
{
	if (cancelled)
		return;

	if (browser->priv->current_file != NULL)
		gth_viewer_page_revert (browser->priv->viewer_page);
	_gth_browser_real_set_current_page (GTH_WINDOW (browser), GPOINTER_TO_INT (user_data));
}
