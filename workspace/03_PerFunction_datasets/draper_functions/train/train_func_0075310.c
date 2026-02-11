folks_presence_details_base_init (FolksPresenceDetailsIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;


		g_object_interface_install_property (iface, g_param_spec_enum ("presence-type", "presence-type", "presence-type", FOLKS_TYPE_PRESENCE_TYPE, FOLKS_PRESENCE_TYPE_UNSET, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));


		g_object_interface_install_property (iface, g_param_spec_string ("presence-message", "presence-message", "presence-message", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));


		g_object_interface_install_property (iface, g_param_spec_boxed ("client-types", "client-types", "client-types", G_TYPE_STRV, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));


		g_object_interface_install_property (iface, g_param_spec_string ("presence-status", "presence-status", "presence-status", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	}
}
