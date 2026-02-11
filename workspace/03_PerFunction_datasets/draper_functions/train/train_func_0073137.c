_dbus_logger_iface_get_favourite_contacts_ready (GObject * source_object, GAsyncResult * _res_, gpointer _user_data_) {
	GDBusMethodInvocation * invocation;
	GError* error = NULL;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	AccountFavourites* result;
	int result_length1 = 0;
	AccountFavourites* _tmp20_;
	GVariantBuilder _tmp21_;
	int _tmp22_;
	invocation = _user_data_;
	result = logger_iface_get_favourite_contacts_finish ((LoggerIface*) source_object, _res_, &result_length1, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	_tmp20_ = result;
	g_variant_builder_init (&_tmp21_, G_VARIANT_TYPE ("a(oas)"));
	for (_tmp22_ = 0; _tmp22_ < result_length1; _tmp22_++) {
		GVariantBuilder _tmp23_;
		gchar** _tmp24_;
		GVariantBuilder _tmp25_;
		int _tmp26_;
		g_variant_builder_init (&_tmp23_, G_VARIANT_TYPE_TUPLE);
		g_variant_builder_add_value (&_tmp23_, g_variant_new_object_path ((*_tmp20_).account_path));
		_tmp24_ = (*_tmp20_).ids;
		g_variant_builder_init (&_tmp25_, G_VARIANT_TYPE ("as"));
		for (_tmp26_ = 0; _tmp26_ < (*_tmp20_).ids_length1; _tmp26_++) {
			g_variant_builder_add_value (&_tmp25_, g_variant_new_string (*_tmp24_));
			_tmp24_++;
		}
		g_variant_builder_add_value (&_tmp23_, g_variant_builder_end (&_tmp25_));
		g_variant_builder_add_value (&_tmp21_, g_variant_builder_end (&_tmp23_));
		_tmp20_++;
	}
	g_variant_builder_add_value (&_reply_builder, g_variant_builder_end (&_tmp21_));
	result = (_vala_AccountFavourites_array_free (result, result_length1), NULL);
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
