_dbus_dvb_id_bus_channel_list_GetChannelInfos (DVBIDBusChannelList* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GError* error = NULL;
	GVariantIter _arguments_iter;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	DVBChannelInfo* result;
	int result_length1 = 0;
	DVBChannelInfo* _tmp77_;
	GVariantBuilder _tmp78_;
	int _tmp79_;
	g_variant_iter_init (&_arguments_iter, parameters);
	result = dvb_id_bus_channel_list_GetChannelInfos (self, &result_length1, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	_tmp77_ = result;
	g_variant_builder_init (&_tmp78_, G_VARIANT_TYPE ("a(usb)"));
	for (_tmp79_ = 0; _tmp79_ < result_length1; _tmp79_++) {
		GVariantBuilder _tmp80_;
		g_variant_builder_init (&_tmp80_, G_VARIANT_TYPE_TUPLE);
		g_variant_builder_add_value (&_tmp80_, g_variant_new_uint32 ((*_tmp77_).id));
		g_variant_builder_add_value (&_tmp80_, g_variant_new_string ((*_tmp77_).name));
		g_variant_builder_add_value (&_tmp80_, g_variant_new_boolean ((*_tmp77_).is_radio));
		g_variant_builder_add_value (&_tmp78_, g_variant_builder_end (&_tmp80_));
		_tmp77_++;
	}
	g_variant_builder_add_value (&_reply_builder, g_variant_builder_end (&_tmp78_));
	result = (_vala_DVBChannelInfo_array_free (result, result_length1), NULL);
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
