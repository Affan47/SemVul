hitori_window_state_event_cb (GtkWindow *window, GdkEventWindowState *event, Hitori *hitori)
{
	if (hitori->debug)
		g_debug ("Got window state event: %u (changed: %u)", event->new_window_state, event->changed_mask);

	if (event->new_window_state & GDK_WINDOW_STATE_WITHDRAWN ||
	    event->new_window_state & GDK_WINDOW_STATE_ICONIFIED ||
	    event->new_window_state & GDK_WINDOW_STATE_BELOW) {

		hitori_pause_timer (hitori);
	} else {

		hitori_start_timer (hitori);
	}
}
