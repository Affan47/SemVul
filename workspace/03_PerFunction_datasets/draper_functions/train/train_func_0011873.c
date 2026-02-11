gx_hslider_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (slider_set_from_pointer(widget, event->state, event->x, event->y, FALSE, event->button, event)) {
		gtk_grab_add(widget);
	}
	return FALSE;
}
