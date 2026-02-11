free_smartphone_usage_sync_proxy_suspend (FreeSmartphoneUsageSync* self, GError** error) {
	GDBusMessage *_message;
	GVariant *_arguments;
	GVariantBuilder _arguments_builder;
	GDBusMessage *_reply_message;
	FREE_SMARTPHONE_USAGE_ERROR;
	FREE_SMARTPHONE_ERROR;
	G_DBUS_ERROR;
	G_IO_ERROR;
	_message = g_dbus_message_new_method_call (g_dbus_proxy_get_name ((GDBusProxy *) self), g_dbus_proxy_get_object_path ((GDBusProxy *) self), "org.freesmartphone.Usage", "Suspend");
	g_variant_builder_init (&_arguments_builder, G_VARIANT_TYPE_TUPLE);
	_arguments = g_variant_builder_end (&_arguments_builder);
	g_dbus_message_set_body (_message, _arguments);
	_reply_message = g_dbus_connection_send_message_with_reply_sync (g_dbus_proxy_get_connection ((GDBusProxy *) self), _message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, g_dbus_proxy_get_default_timeout ((GDBusProxy *) self), NULL, NULL, error);
	g_object_unref (_message);
	if (!_reply_message) {
		return;
	}
	if (g_dbus_message_to_gerror (_reply_message, error)) {
		g_object_unref (_reply_message);
		return;
	}
	g_object_unref (_reply_message);
}
