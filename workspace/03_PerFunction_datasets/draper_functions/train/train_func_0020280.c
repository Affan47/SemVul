seahorse_widget_new_allow_multiple (const gchar *name, GtkWindow *parent)
{
	GtkWindow *window;
	SeahorseWidget *swidget;

	swidget = g_object_new (SEAHORSE_TYPE_WIDGET, "name", name,  NULL);

	if (parent != NULL) {
		window = GTK_WINDOW (seahorse_widget_get_widget (swidget, swidget->name));
		gtk_window_set_transient_for (window, parent);
	}

	gtk_builder_connect_signals (swidget->gtkbuilder, NULL);
	return swidget;
}
