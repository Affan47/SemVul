unity_protocol_scope_service_dbus_proxy_get_metadata (UnityProtocolScopeService* self) {
	GVariant *_inner_reply;
	GHashTable* _result;
	GHashTable* _tmp55_;
	GVariantIter _tmp56_;
	GVariant* _tmp57_;
	GVariant* _tmp58_;
	_inner_reply = g_dbus_proxy_get_cached_property ((GDBusProxy *) self, "Metadata");
	if (!_inner_reply) {
		GVariant *_arguments;
		GVariant *_reply;
		GVariantBuilder _arguments_builder;
		g_variant_builder_init (&_arguments_builder, G_VARIANT_TYPE_TUPLE);
		g_variant_builder_add_value (&_arguments_builder, g_variant_new_string ("com.canonical.Unity.Scope"));
		g_variant_builder_add_value (&_arguments_builder, g_variant_new_string ("Metadata"));
		_arguments = g_variant_builder_end (&_arguments_builder);
		_reply = g_dbus_proxy_call_sync ((GDBusProxy *) self, "org.freedesktop.DBus.Properties.Get", _arguments, G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL);
		if (!_reply) {
			return NULL;
		}
		g_variant_get (_reply, "(v)", &_inner_reply);
		g_variant_unref (_reply);
	}
	_tmp55_ = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	g_variant_iter_init (&_tmp56_, _inner_reply);
	while (g_variant_iter_loop (&_tmp56_, "{?*}", &_tmp57_, &_tmp58_)) {
		g_hash_table_insert (_tmp55_, g_variant_dup_string (_tmp57_, NULL), g_variant_dup_string (_tmp58_, NULL));
	}
	_result = _tmp55_;
	g_variant_unref (_inner_reply);
	return _result;
}
