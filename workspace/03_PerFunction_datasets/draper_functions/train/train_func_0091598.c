unity_protocol_scope_service_proxy_activate_async (UnityProtocolScopeService* self, const gchar* channel_id, GVariant** result_arr, int result_arr_length1, guint action_type, GHashTable* hints, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	GDBusMessage *_message;
	GVariant *_arguments;
	GVariantBuilder _arguments_builder;
	GVariant** _tmp7_;
	GVariantBuilder _tmp8_;
	int _tmp9_;
	GVariantBuilder _tmp10_;
	GHashTableIter _tmp11_;
	gpointer _tmp12_;
	gpointer _tmp13_;
	G_IO_ERROR;
	UNITY_PROTOCOL_SCOPE_ERROR;
	_message = g_dbus_message_new_method_call (g_dbus_proxy_get_name ((GDBusProxy *) self), g_dbus_proxy_get_object_path ((GDBusProxy *) self), "com.canonical.Unity.Scope", "Activate");
	g_variant_builder_init (&_arguments_builder, G_VARIANT_TYPE_TUPLE);
	g_variant_builder_add_value (&_arguments_builder, g_variant_new_string (channel_id));
	_tmp7_ = result_arr;
	g_variant_builder_init (&_tmp8_, G_VARIANT_TYPE ("av"));
	for (_tmp9_ = 0; _tmp9_ < result_arr_length1; _tmp9_++) {
		g_variant_builder_add_value (&_tmp8_, g_variant_new_variant (*_tmp7_));
		_tmp7_++;
	}
	g_variant_builder_add_value (&_arguments_builder, g_variant_builder_end (&_tmp8_));
	g_variant_builder_add_value (&_arguments_builder, g_variant_new_uint32 (action_type));
	g_hash_table_iter_init (&_tmp11_, hints);
	g_variant_builder_init (&_tmp10_, G_VARIANT_TYPE ("a{sv}"));
	while (g_hash_table_iter_next (&_tmp11_, &_tmp12_, &_tmp13_)) {
		gchar* _key;
		GVariant* _value;
		_key = (gchar*) _tmp12_;
		_value = (GVariant*) _tmp13_;
		g_variant_builder_add (&_tmp10_, "{?*}", g_variant_new_string (_key), g_variant_new_variant (_value));
	}
	g_variant_builder_add_value (&_arguments_builder, g_variant_builder_end (&_tmp10_));
	_arguments = g_variant_builder_end (&_arguments_builder);
	g_dbus_message_set_body (_message, _arguments);
	g_dbus_connection_send_message_with_reply (g_dbus_proxy_get_connection ((GDBusProxy *) self), _message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, g_dbus_proxy_get_default_timeout ((GDBusProxy *) self), NULL, cancellable, _vala_g_async_ready_callback, g_simple_async_result_new ((GObject *) self, _callback_, _user_data_, NULL));
	g_object_unref (_message);
}
