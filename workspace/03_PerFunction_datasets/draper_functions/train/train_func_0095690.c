duration_units_changed_cb (GtkWidget* widget, Application* self) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (widget != NULL);
	application_save_duration (self);
}
