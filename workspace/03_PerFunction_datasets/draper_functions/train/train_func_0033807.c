manage_window_focus_out(GtkWidget *widget, GdkEventFocus *event,
			     gpointer data)
{


	if (!GTK_IS_WINDOW(widget))
		return FALSE;


	if (focus_window == widget)
		focus_window = NULL;

	return FALSE;
}
