_gth_browser_set_current_page (GthWindow *window,
			       int        page)
{
	GthBrowser *browser = GTH_BROWSER (window);

	if (page == gth_window_get_current_page (window))
		return;

	if (g_settings_get_boolean (browser->priv->messages_settings, PREF_MSG_SAVE_MODIFIED_IMAGE)
	    && gth_browser_get_file_modified (browser))
	{
		gth_browser_ask_whether_to_save (browser,
						 set_current_page__file_saved_cb,
						 GINT_TO_POINTER (page));
	}
	else
		_gth_browser_real_set_current_page (window, page);
}
