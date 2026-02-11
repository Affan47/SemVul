free_smartphone_device_idle_notifier_proxy_get_state_finish (FreeSmartphoneDeviceIdleNotifier* self, GAsyncResult* _res_, GError** error) {
	GDBusMessage *_reply_message;
	GVariant *_reply;
	GVariantIter _reply_iter;
	FreeSmartphoneDeviceIdleState _result;
	GVariant* _tmp389_;
	_reply_message = g_dbus_connection_send_message_with_reply_finish (g_dbus_proxy_get_connection ((GDBusProxy *) self), g_simple_async_result_get_op_res_gpointer ((GSimpleAsyncResult *) _res_), error);
	if (!_reply_message) {
		return 0;
	}
	if (g_dbus_message_to_gerror (_reply_message, error)) {
		g_object_unref (_reply_message);
		return 0;
	}
	_reply = g_dbus_message_get_body (_reply_message);
	g_variant_iter_init (&_reply_iter, _reply);
	_tmp389_ = g_variant_iter_next_value (&_reply_iter);
	_result = free_smartphone_device_idle_state_from_string (g_variant_get_string (_tmp389_, NULL), error);
	g_variant_unref (_tmp389_);
	if (error && (*error)) {
		g_object_unref (_reply_message);
		return 0;
	}
	g_object_unref (_reply_message);
	return _result;
}
