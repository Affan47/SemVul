click_expander_cb (GObject * object,
                   GParamSpec * param_spec,
                   gpointer data)
{
	GSearchWindow * gsearch = data;

	if (gtk_expander_get_expanded (GTK_EXPANDER (object)) == TRUE) {
		gtk_widget_show (gsearch->available_options_vbox);
		gtk_window_set_geometry_hints (GTK_WINDOW (gsearch->window),
		                               GTK_WIDGET (gsearch->window),
		                               &gsearch->window_geometry,
		                               GDK_HINT_MIN_SIZE);
	}
	else {
		GdkGeometry default_geometry = {MINIMUM_WINDOW_WIDTH, MINIMUM_WINDOW_HEIGHT};

		gtk_widget_hide (gsearch->available_options_vbox);
		gtk_window_set_geometry_hints (GTK_WINDOW (gsearch->window),
		                               GTK_WIDGET (gsearch->window),
		                               &default_geometry,
		                               GDK_HINT_MIN_SIZE);
	}
}
