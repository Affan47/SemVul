unity_protocol_scope_service_dbus_proxy_get_visible (UnityProtocolScopeService* self) {
	GVariant *_inner_reply;
	gboolean _result;
	_inner_reply = g_dbus_proxy_get_cached_property ((GDBusProxy *) self, "Visible");
	if (!_inner_reply) {
		GVariant *_arguments;
		GVariant *_reply;
		GVariantBuilder _arguments_builder;
		g_variant_builder_init (&_arguments_builder, G_VARIANT_TYPE_TUPLE);
		g_variant_builder_add_value (&_arguments_builder, g_variant_new_string ("com.canonical.Unity.Scope"));
		g_variant_builder_add_value (&_arguments_builder, g_variant_new_string ("Visible"));
		_arguments = g_variant_builder_end (&_arguments_builder);
		_reply = g_dbus_proxy_call_sync ((GDBusProxy *) self, "org.freedesktop.DBus.Properties.Get", _arguments, G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL);
		if (!_reply) {
			return FALSE;
		}
		g_variant_get (_reply, "(v)", &_inner_reply);
		g_variant_unref (_reply);
	}
	_result = g_variant_get_boolean (_inner_reply);
	g_variant_unref (_inner_reply);
	return _result;
}
