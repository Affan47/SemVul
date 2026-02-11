gtk_service_destroy(GtkWidget *widget)
{
	GtkService *service = GTK_SERVICE(widget);
	GtkServicePrivate *priv = service->priv;

	if (priv != NULL && priv->selected == FALSE) {

		connman_service_set_property_changed_callback(service->path,
								NULL, service);
		connman_technology_set_property_error_callback(service->path,
								NULL, service);
	}

	GTK_WIDGET_CLASS(gtk_service_parent_class)->destroy(widget);
}
