button_press_event (GtkWidget *self, GdkEventButton *event)
{
	GtkAllocation allocation;
	gint window_x, window_y;

	if (event->type != GDK_BUTTON_PRESS) {
		return TRUE;
	}


	gdk_window_get_position (gtk_widget_get_window (self), &window_x, &window_y);
	gtk_widget_get_allocation (self, &allocation);


	if (event->x_root < window_x || event->x_root > window_x + allocation.width ||
	    event->y_root < window_y || event->y_root > window_y + allocation.height) {
		almanah_calendar_window_popdown (ALMANAH_CALENDAR_WINDOW (self));
	}

	return FALSE;
}
