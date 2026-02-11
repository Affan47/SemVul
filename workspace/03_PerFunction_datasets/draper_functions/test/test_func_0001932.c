apply_window_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (applywindow.busy)
		return FALSE;
	if (event && event->keyval == GDK_KEY_Escape)
		apply_window_close();
	else if (event && event->keyval == GDK_KEY_Delete)
		apply_popup_delete(NULL, NULL);
	return FALSE;
}
