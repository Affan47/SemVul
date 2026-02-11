nautilus_window_hide_sidebar (NautilusWindow *window)
{
	DEBUG ("Called hide_sidebar()");

	if (window->details->sidebar == NULL) {
		return;
	}

	nautilus_window_tear_down_sidebar (window);
}
