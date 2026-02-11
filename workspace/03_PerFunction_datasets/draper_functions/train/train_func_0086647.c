_dbus_dvb_id_bus_scanner_WriteChannelsToFile (DVBIDBusScanner* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GError* error = NULL;
	GVariantIter _arguments_iter;
	guint* channel_sids = NULL;
	int channel_sids_length1 = 0;
	GVariant* _tmp362_;
	guint* _tmp363_;
	int _tmp363__length;
	int _tmp363__size;
	int _tmp363__length1;
	GVariantIter _tmp364_;
	GVariant* _tmp365_;
	gchar* path = NULL;
	GVariant* _tmp366_;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	gboolean result;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp362_ = g_variant_iter_next_value (&_arguments_iter);
	_tmp363_ = g_new (guint, 5);
	_tmp363__length = 0;
	_tmp363__size = 4;
	_tmp363__length1 = 0;
	g_variant_iter_init (&_tmp364_, _tmp362_);
	for (; (_tmp365_ = g_variant_iter_next_value (&_tmp364_)) != NULL; _tmp363__length1++) {
		if (_tmp363__size == _tmp363__length) {
			_tmp363__size = 2 * _tmp363__size;
			_tmp363_ = g_renew (guint, _tmp363_, _tmp363__size + 1);
		}
		_tmp363_[_tmp363__length++] = g_variant_get_uint32 (_tmp365_);
		g_variant_unref (_tmp365_);
	}
	channel_sids_length1 = _tmp363__length1;
	channel_sids = _tmp363_;
	g_variant_unref (_tmp362_);
	_tmp366_ = g_variant_iter_next_value (&_arguments_iter);
	path = g_variant_dup_string (_tmp366_, NULL);
	g_variant_unref (_tmp366_);
	result = dvb_id_bus_scanner_WriteChannelsToFile (self, channel_sids, channel_sids_length1, path, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	g_variant_builder_add_value (&_reply_builder, g_variant_new_boolean (result));
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	channel_sids = (g_free (channel_sids), NULL);
	_g_free0 (path);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
