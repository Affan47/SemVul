service_set_name(GtkService *service)
{
	const char *name;
	char *markup;

	name = connman_service_get_name(service->path);
	if (name == NULL)
		name = "- Hidden -";

	if (connman_service_is_favorite(service->path) == TRUE) {
		if (g_strcmp0(connman_service_get_type(service->path),
							"wifi") == 0) {
			markup = g_markup_printf_escaped(
				"<b>%s</b> <i> (%s) </i>",
				name,
				connman_service_get_security(service->path));
		} else
			markup = g_markup_printf_escaped("<b>%s</b>", name);
	} else {
		if (g_strcmp0(connman_service_get_type(service->path),
							"wifi") == 0) {
			markup = g_markup_printf_escaped(
				"%s  <i> (%s) </i>", name,
				connman_service_get_security(service->path));
		} else
			markup = g_markup_printf_escaped("%s", name);
	}

	gtk_label_set_markup(service->priv->name, markup);

	g_free(markup);
}
