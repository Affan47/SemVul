e_module_load (GTypeModule *type_module)
{
	GSettings *settings;
	gchar **disabled_plugins;
	gint i = 0;

	settings = g_settings_new ("org.gnome.evolution");
	disabled_plugins = g_settings_get_strv (settings, "disabled-eplugins");

	for (i = 0; disabled_plugins && disabled_plugins[i] != NULL; i++) {

		if (g_strcmp0 (
			disabled_plugins[i],
			"org.gnome.evolution.plugin.preferPlain") == 0) {

			g_strfreev (disabled_plugins);
			g_object_unref (settings);
			return;
		}

	}

	e_mail_parser_prefer_plain_type_register (type_module);
	e_mail_display_popup_prefer_plain_type_register (type_module);

	g_strfreev (disabled_plugins);
	g_object_unref (settings);
}
