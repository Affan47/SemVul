e_source_config_add_secure_connection_for_webdav (ESourceConfig *config,
                                                  ESource *scratch_source)
{
	GtkWidget *widget;
	ESourceExtension *extension;
	ESourceAuthentication *authentication_extension;
	const gchar *extension_name;
	const gchar *label;

	g_return_if_fail (E_IS_SOURCE_CONFIG (config));
	g_return_if_fail (E_IS_SOURCE (scratch_source));

	extension_name = E_SOURCE_EXTENSION_SECURITY;
	extension = e_source_get_extension (scratch_source, extension_name);

	label = _("Use a secure connection");
	widget = gtk_check_button_new_with_label (label);
	e_source_config_insert_widget (config, scratch_source, NULL, widget);
	gtk_widget_show (widget);

	g_object_bind_property (
		extension, "secure",
		widget, "active",
		G_BINDING_BIDIRECTIONAL |
		G_BINDING_SYNC_CREATE);

	extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
	authentication_extension =
		e_source_get_extension (scratch_source, extension_name);

	g_object_bind_property_full (
		extension, "secure",
		authentication_extension, "port",
		G_BINDING_DEFAULT,
		secure_to_port_cb,
		NULL, NULL, NULL);

	extension_name = E_SOURCE_EXTENSION_WEBDAV_BACKEND;
	extension = e_source_get_extension (scratch_source, extension_name);

	widget = gtk_button_new_with_mnemonic (
		_("Unset _trust for SSL certificate"));
	gtk_widget_set_margin_left (widget, 24);
	e_source_config_insert_widget (config, scratch_source, NULL, widget);
	gtk_widget_show (widget);

	g_object_bind_property_full (
		extension, "ssl-trust",
		widget, "sensitive",
		G_BINDING_SYNC_CREATE,
		webdav_source_ssl_trust_to_sensitive_cb,
		NULL, NULL, NULL);

	g_signal_connect (
		widget, "clicked",
		G_CALLBACK (webdav_unset_ssl_trust_clicked_cb), extension);
}
