nemo_window_hide_sidebar (NemoWindow *window)
{
	DEBUG ("Called hide_sidebar()");

	if (window->details->sidebar == NULL) {
		return;
	}

	nemo_window_tear_down_sidebar (window);
	nemo_window_update_show_hide_menu_items (window);

    nemo_window_set_show_sidebar (window, FALSE);
}
