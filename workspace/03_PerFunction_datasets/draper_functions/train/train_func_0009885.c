setup_side_pane_width (NemoWindow *window)
{
	g_return_if_fail (window->details->sidebar != NULL);

	window->details->side_pane_width =
		g_settings_get_int (nemo_window_state,
				    NEMO_WINDOW_STATE_SIDEBAR_WIDTH);

	gtk_paned_set_position (GTK_PANED (window->details->content_paned),
				window->details->side_pane_width);
}
