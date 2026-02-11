cb_motion_notify_event(GtkWidget      *widget,
                                       GdkEventMotion *event,
                                       gpointer        data)
{
	gint             x, y, tmp;
	GdkModifierType  state;
	WejpScroller    *ws = WEJPSCROLLER(data);

	if (event->is_hint) {
		gdk_window_get_pointer(event->window, &x, &y, &state);
	} else {
		x = event->x;
		y = event->y;
		state = event->state;
	}

	if (state & GDK_BUTTON1_MASK && ws->scroll == FALSE) {
		tmp = ws->mouse_x - x;
		if ((gint)ws->pos + tmp > 0 &&
		    (gint)ws->pos + tmp <
		    ws->extents.width + ws->drawing_area->allocation.width) {
			ws->pos = ws->pos + tmp;
		} else if ((gint)ws->pos + tmp >
		           ws->extents.width + ws->drawing_area->allocation.width) {
			ws->pos = 0;
		} else {
			ws->pos = ws->extents.width + ws->drawing_area->allocation.width;
		}
		ws->mouse_x = x;
	}
	return TRUE;
}
