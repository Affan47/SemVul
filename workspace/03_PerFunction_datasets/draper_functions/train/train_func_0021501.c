content_bar_response_cb (GtkInfoBar *infobar,
			 gint response_id,
			 gpointer user_data)
{
	GAppInfo *default_app;
	NautilusXContentBar *bar = user_data;

	if (response_id < 0) {
		return;
	}

	if (bar->priv->x_content_types == NULL ||
	    bar->priv->mount == NULL)
		return;


 	default_app = g_app_info_get_default_for_type (bar->priv->x_content_types[response_id], FALSE);
	if (default_app != NULL) {
		nautilus_launch_application_for_mount (default_app, bar->priv->mount,
						       GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (bar))));
		g_object_unref (default_app);
	}
}
