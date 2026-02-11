gtk_technology_new(const gchar *path)
{
	GtkTechnology *technology;
	GtkTechnologyPrivate *priv;
	gchar *path_copy, *label;
	gboolean enabled;

	if (path == NULL)
		return NULL;

	path_copy = g_strdup(path);
	if (path_copy == NULL)
		return NULL;

	technology = g_object_new(GTK_TYPE_TECHNOLOGY, NULL);
	if (technology == NULL) {
		g_free(path_copy);
		return NULL;
	}

	priv = technology->priv;
	technology->path = path_copy;

	connman_technology_set_property_changed_callback(path_copy,
					technology_property_changed_cb,
					technology);
	connman_technology_set_property_error_callback(technology->path,
				technology_property_error_cb, technology);

	if (g_strcmp0(connman_technology_get_type(path_copy), "wifi") == 0) {
		gtk_widget_set_tooltip_text(GTK_WIDGET(technology),
				_("Left click to enable/disable\n"
				"Right click to set tethering information"));
	} else
		gtk_widget_set_tooltip_text(GTK_WIDGET(technology),
						_("Left to enable/disable"));

	enabled = connman_technology_is_enabled(path_copy);
	gtk_switch_set_active(priv->enabler, enabled);

	label = g_strdup_printf("via: %s",
				connman_technology_get_name(path_copy));

	priv->tethering = (GtkCheckMenuItem *)
				gtk_check_menu_item_new_with_label(label);
	if (enabled == FALSE)
		gtk_widget_set_sensitive((GtkWidget *)priv->tethering, FALSE);

	set_technology_name(technology, enabled);

	gtk_check_menu_item_set_active(priv->tethering,
				connman_technology_is_tethering(path_copy));

	gtk_widget_set_visible((GtkWidget *)priv->tethering, TRUE);

	g_signal_connect(priv->tethering, "button-release-event",
				G_CALLBACK(gtk_technology_tethering_button),
				technology);

	return technology;
}
