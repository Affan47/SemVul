org_bluez_adapter_proxy_create_paired_device (orgbluezAdapter* self, const gchar* address, const char* agent, const gchar* capability, GError** error) {
	GDBusMessage *_message;
	GVariant *_arguments;
	GVariantBuilder _arguments_builder;
	GDBusMessage *_reply_message;
	GVariant *_reply;
	GVariantIter _reply_iter;
	char* _result;
	GVariant* _tmp69_;
	G_DBUS_ERROR;
	G_IO_ERROR;
	_message = g_dbus_message_new_method_call (g_dbus_proxy_get_name ((GDBusProxy *) self), g_dbus_proxy_get_object_path ((GDBusProxy *) self), "org.bluez.Adapter", "CreatePairedDevice");
	g_variant_builder_init (&_arguments_builder, G_VARIANT_TYPE_TUPLE);
	g_variant_builder_add_value (&_arguments_builder, g_variant_new_string (address));
	g_variant_builder_add_value (&_arguments_builder, g_variant_new_object_path (agent));
	g_variant_builder_add_value (&_arguments_builder, g_variant_new_string (capability));
	_arguments = g_variant_builder_end (&_arguments_builder);
	g_dbus_message_set_body (_message, _arguments);
	_reply_message = g_dbus_connection_send_message_with_reply_sync (g_dbus_proxy_get_connection ((GDBusProxy *) self), _message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, g_dbus_proxy_get_default_timeout ((GDBusProxy *) self), NULL, NULL, error);
	g_object_unref (_message);
	if (!_reply_message) {
		return NULL;
	}
	if (g_dbus_message_to_gerror (_reply_message, error)) {
		g_object_unref (_reply_message);
		return NULL;
	}
	_reply = g_dbus_message_get_body (_reply_message);
	g_variant_iter_init (&_reply_iter, _reply);
	_tmp69_ = g_variant_iter_next_value (&_reply_iter);
	_result = g_variant_dup_string (_tmp69_, NULL);
	g_variant_unref (_tmp69_);
	g_object_unref (_reply_message);
	return _result;
}
