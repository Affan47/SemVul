gui_gtk_monitor_record_button_event(GtkWidget *w, gpointer _monitor)
{
	GuiGtkMonitor *monitor = (GuiGtkMonitor *) _monitor;

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w))) {
		g_signal_emit(G_OBJECT(monitor),
				gui_gtk_monitor_signals[RECORDING_ON], 0);
	} else {
		g_signal_emit(G_OBJECT(monitor),
				gui_gtk_monitor_signals[RECORDING_OFF], 0);
	}
}
