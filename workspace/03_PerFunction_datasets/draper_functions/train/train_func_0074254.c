update_provider(void)
{
	const struct connman_provider *provider;

	provider = connman_service_get_provider(path);

	if (provider == NULL) {
		set_label(builder, "provider_host", "", "");
		set_label(builder, "provider_domain", "", "");
		set_label(builder, "provider_name", "", "");
		set_label(builder, "provider_type", "", "");

		set_widget_sensitive(builder, "provider_settings", FALSE);

		return;
	}

	set_label(builder, "provider_host", provider->host, "");
	set_label(builder, "provider_domain", provider->domain, "");
	set_label(builder, "provider_name", provider->name, "");
	set_label(builder, "provider_type", provider->type, "");

	set_widget_sensitive(builder, "provider_settings", TRUE);
}
