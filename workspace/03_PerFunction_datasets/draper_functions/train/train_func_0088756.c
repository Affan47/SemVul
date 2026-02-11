_dbus_free_smartphone_device_led_sync_blink_seconds (FreeSmartphoneDeviceLEDSync* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GError* error = NULL;
	GVariantIter _arguments_iter;
	gint seconds = 0;
	GVariant* _tmp427_;
	gint on_duration = 0;
	GVariant* _tmp428_;
	gint off_duration = 0;
	GVariant* _tmp429_;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp427_ = g_variant_iter_next_value (&_arguments_iter);
	seconds = g_variant_get_int32 (_tmp427_);
	g_variant_unref (_tmp427_);
	_tmp428_ = g_variant_iter_next_value (&_arguments_iter);
	on_duration = g_variant_get_int32 (_tmp428_);
	g_variant_unref (_tmp428_);
	_tmp429_ = g_variant_iter_next_value (&_arguments_iter);
	off_duration = g_variant_get_int32 (_tmp429_);
	g_variant_unref (_tmp429_);
	free_smartphone_device_led_sync_blink_seconds (self, seconds, on_duration, off_duration, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
