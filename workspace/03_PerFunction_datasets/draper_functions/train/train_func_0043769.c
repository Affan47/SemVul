settings_window_new(gboolean exit)
{
	START_FUNC
	GError* error = NULL;
	settings_window=g_malloc(sizeof(struct settings_window));
	memset(settings_window, 0, sizeof(struct settings_window));

	settings_window->gtk_exit=exit;
	settings_window->gtkbuilder=gtk_builder_new();
	if (!gtk_builder_add_from_file(settings_window->gtkbuilder, DATADIR "/florence.glade", &error))
	{
		flo_warn(_("Couldn't load builder file: %s"), error->message);
		g_error_free(error);
	}


	settings_window_preview_build();
	settings_window_layouts_populate();
	settings_window_input_method_populate();

	settings_window_update();
	settings_window->notify_id=settings_register_all(
		(settings_callback)settings_window_update);
	settings_transaction();

	gtk_builder_connect_signals(settings_window->gtkbuilder, NULL);


	tools_set_icon(GTK_WINDOW(gtk_builder_get_object(settings_window->gtkbuilder,
		"flo_config_window")));
	END_FUNC
}
