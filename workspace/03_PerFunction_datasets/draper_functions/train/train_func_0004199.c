aqualung_loop_bar_leave_notify(GtkWidget * widget, GdkEventCrossing * event) {

	AqualungLoopBarPrivate * priv;

	if (event->y >= 0 && event->y < widget->allocation.height &&
	    event->x >= 0 && event->x < widget->allocation.width) {


		return FALSE;
	}

	priv = AQUALUNG_LOOP_BAR_GET_PRIVATE(widget);

	priv->start_hover = priv->start_dragged;
	priv->end_hover = priv->end_dragged;

	aqualung_loop_bar_redraw_canvas(widget);

	return FALSE;
}
