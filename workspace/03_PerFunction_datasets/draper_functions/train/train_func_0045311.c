toggle_button_press_event_cb (GtkWidget      *widget,
                              GdkEventButton *event,
                              gpointer        user_data)
{
	GthMenuButton *self = user_data;

	if (event->button == 1)
		g_signal_emit (self, signals[SHOW_MENU], 0);

	return FALSE;
}
