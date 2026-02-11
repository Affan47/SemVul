dialog_button_press_event(
	GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->type == GDK_BUTTON_PRESS || event->type == GDK_2BUTTON_PRESS) {
		gtk_widget_destroy(GTK_WIDGET(data));
	}
	return TRUE;
}
