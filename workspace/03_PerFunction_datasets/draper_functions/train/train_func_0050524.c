gigolo_window_set_toolbar_style(GigoloWindow *window, gint style)
{
	GigoloWindowPrivate *priv = GIGOLO_WINDOW_GET_PRIVATE(window);
	if (style == -1)
	{
		g_object_get(gtk_widget_get_settings(GTK_WIDGET(window)), "gtk-toolbar-style", &style, NULL);
		g_object_set(priv->settings, "toolbar-style", style, NULL);
	}
	else
	{
		gtk_toolbar_set_style(GTK_TOOLBAR(priv->toolbar), style);
	}
}
