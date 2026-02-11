cb_map_event(GtkWidget *widget, GdkEvent *event, gpointer data)
	{


	if (_GK.sticky_state)
		gtk_window_stick(GTK_WINDOW(top_window));
	if (_GK.state_skip_pager)
		gkrellm_winop_state_skip_pager(TRUE);
	if (_GK.state_skip_taskbar)
		gkrellm_winop_state_skip_taskbar(TRUE);
	if (_GK.state_above)
		gkrellm_winop_state_above(TRUE);
	else if (_GK.state_below)
		gkrellm_winop_state_below(TRUE);

	return FALSE;
	}
