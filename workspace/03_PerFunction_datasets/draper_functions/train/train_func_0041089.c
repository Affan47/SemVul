play_queue_plugin_get_type(void)
{
	static GType play_queue_plugin_type_id = 0;
	if (play_queue_plugin_type_id == 0)
	{
		static const GTypeInfo info = {
			.class_size = sizeof(PlayQueuePluginClass),
			.class_init = (GClassInitFunc) play_queue_plugin_class_init,
			.instance_size = sizeof(PlayQueuePlugin),
			.n_preallocs = 0
		};
		static const GInterfaceInfo iface_info = {
			(GInterfaceInitFunc) play_queue_browser_iface_init,
			(GInterfaceFinalizeFunc) NULL, NULL
		};
		static const GInterfaceInfo iface_tm_info = {
			(GInterfaceInitFunc) play_queue_plugin_tool_menu_iface_init,
			(GInterfaceFinalizeFunc) NULL, NULL
		};

		static const GInterfaceInfo iface_is_info = {
			(GInterfaceInitFunc) play_queue_plugin_is_iface_init,
			(GInterfaceFinalizeFunc) NULL, NULL
		};
		play_queue_plugin_type_id = g_type_register_static(GMPC_PLUGIN_TYPE_BASE, "PlayQueuePlugin", &info, 0);

		g_type_add_interface_static(play_queue_plugin_type_id, GMPC_PLUGIN_TYPE_BROWSER_IFACE, &iface_info);
		g_type_add_interface_static(play_queue_plugin_type_id, GMPC_PLUGIN_TYPE_TOOL_MENU_IFACE, &iface_tm_info);
		g_type_add_interface_static(play_queue_plugin_type_id, GMPC_PLUGIN_TYPE_INTEGRATE_SEARCH_IFACE, &iface_is_info);
	}
	return play_queue_plugin_type_id;
}
