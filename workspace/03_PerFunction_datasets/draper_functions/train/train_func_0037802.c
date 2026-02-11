launcher_do_zoom_animation (GtkWidget *widget)
{
	GtkSettings *settings;
	gboolean     enable_animations;

	settings = gtk_widget_get_settings (widget);

	enable_animations = TRUE;
	g_object_get (settings,
		      "gtk-enable-animations", &enable_animations,
		      NULL);

	if (enable_animations)
		xstuff_zoom_animate (widget,
				     button_widget_get_pixbuf (BUTTON_WIDGET (widget)),
				     button_widget_get_orientation (BUTTON_WIDGET (widget)),
				     NULL);
}
