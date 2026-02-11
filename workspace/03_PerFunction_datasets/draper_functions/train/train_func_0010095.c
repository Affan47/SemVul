search_window_keypress_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	SearchData *sd = data;
	gboolean stop_signal = FALSE;

	if (event->state & GDK_CONTROL_MASK)
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case 'T': case 't':
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->button_thumbs),
					!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->button_thumbs)));
				break;
			case 'W': case 'w':
				search_window_close(sd);
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}

	return stop_signal;
}
