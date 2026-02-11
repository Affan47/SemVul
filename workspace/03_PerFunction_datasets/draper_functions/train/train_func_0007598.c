nautilus_window_tear_down_sidebar (NautilusWindow *window)
{
	DEBUG ("Destroying sidebar");

	if (window->details->sidebar != NULL) {
		gtk_widget_destroy (GTK_WIDGET (window->details->sidebar));
		window->details->sidebar = NULL;
		window->details->places_sidebar = NULL;
	}
}
