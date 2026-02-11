panel_applet_container_get_applet (PanelAppletContainer *container,
				   GdkScreen            *screen,
				   const gchar          *iid,
				   GVariant             *props,
				   GCancellable         *cancellable,
				   GAsyncReadyCallback   callback,
				   gpointer              user_data)
{
	GSimpleAsyncResult *result;
	AppletFactoryData  *data;
	gint                screen_number;
	gchar              *bus_name;
	gchar              *factory_id;
	gchar              *applet_id;

	result = g_simple_async_result_new (G_OBJECT (container),
					    callback,
					    user_data,
					    panel_applet_container_get_applet);

	applet_id = g_strrstr (iid, "::");
	if (!applet_id) {
		g_simple_async_result_set_error (result,
						 PANEL_APPLET_CONTAINER_ERROR,
						 PANEL_APPLET_CONTAINER_INVALID_APPLET,
						 "Invalid applet iid: %s", iid);
		g_simple_async_result_complete (result);
		g_object_unref (result);

		return;
	}

	factory_id = g_strndup (iid, strlen (iid) - strlen (applet_id));
	applet_id += 2;


	screen_number = gdk_screen_get_number (screen);

	data = g_new (AppletFactoryData, 1);
	data->result = result;
	data->factory_id = factory_id;
	data->parameters = g_variant_new ("(si*)", applet_id, screen_number, props);
	data->cancellable = cancellable ? g_object_ref (cancellable) : NULL;

	bus_name = g_strdup_printf (PANEL_APPLET_BUS_NAME, factory_id);

	container->priv->name_watcher_id =
		g_bus_watch_name (G_BUS_TYPE_SESSION,
				  bus_name,
				  G_BUS_NAME_WATCHER_FLAGS_AUTO_START,
				  (GBusNameAppearedCallback) on_factory_appeared,
				  NULL,
				  data,
				  (GDestroyNotify) applet_factory_data_free);

	g_free (bus_name);
}
