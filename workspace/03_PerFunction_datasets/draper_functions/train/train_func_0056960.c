gth_browser_viewer_button_press_cb (GthBrowser     *browser,
				    GdkEventButton *event)
{
	g_return_val_if_fail (event != NULL, FALSE);

	if (event->button == 3) {
		gth_browser_file_menu_popup (browser, event);
		return TRUE;
	}

	return FALSE;
}
