_dbus_logger_iface_add_favourite_contact_ready (GObject * source_object, GAsyncResult * _res_, gpointer _user_data_) {
	GDBusMethodInvocation * invocation;
	GError* error = NULL;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	invocation = _user_data_;
	logger_iface_add_favourite_contact_finish ((LoggerIface*) source_object, _res_, &error);
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
