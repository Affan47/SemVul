overlay_enter_notify_cb (GtkWidget        *parent,
			 GdkEventCrossing *event,
			 gpointer          user_data)
{
	GtkWidget *widget = user_data;

	if (event->window != gtk_widget_get_window (widget)) {
		return FALSE;
	}

	if (NEMO_FLOATING_BAR (widget)->priv->is_interactive) {
		return FALSE;
	}

	if (gtk_widget_get_halign (widget) == GTK_ALIGN_START) {
		gtk_widget_set_halign (widget, GTK_ALIGN_END);
	} else {
		gtk_widget_set_halign (widget, GTK_ALIGN_START);
	}

	gtk_widget_queue_resize (widget);

	return FALSE;
}
