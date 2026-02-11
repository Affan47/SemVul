_dbus_free_smartphone_audio_manager_get_available_devices_ready (GObject * source_object, GAsyncResult * _res_, gpointer _user_data_) {
	GDBusMethodInvocation * invocation;
	GError* error = NULL;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	FreeSmartphoneAudioDevice* result;
	int result_length1 = 0;
	FreeSmartphoneAudioDevice* _tmp2844_;
	GVariantBuilder _tmp2845_;
	int _tmp2846_;
	invocation = _user_data_;
	result = free_smartphone_audio_manager_get_available_devices_finish ((FreeSmartphoneAudioManager*) source_object, _res_, &result_length1, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	_tmp2844_ = result;
	g_variant_builder_init (&_tmp2845_, G_VARIANT_TYPE ("as"));
	for (_tmp2846_ = 0; _tmp2846_ < result_length1; _tmp2846_++) {
		g_variant_builder_add_value (&_tmp2845_, g_variant_new_string (free_smartphone_audio_device_to_string (*_tmp2844_)));
		_tmp2844_++;
	}
	g_variant_builder_add_value (&_reply_builder, g_variant_builder_end (&_tmp2845_));
	result = (g_free (result), NULL);
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
