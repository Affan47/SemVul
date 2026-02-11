zeitgeist_remote_search_engine_proxy_search_with_relevancies_finish (ZeitgeistRemoteSearchEngine* self, GAsyncResult* _res_, GVariant** events, gdouble** relevancies, int* relevancies_length1, guint* matches, GError** error) {
	GDBusMessage *_reply_message;
	GVariant *_reply;
	GVariantIter _reply_iter;
	GVariant* _vala_events;
	gdouble* _vala_relevancies;
	int _vala_relevancies_length1;
	GVariant* _tmp1_;
	gdouble* _tmp2_;
	int _tmp2__length;
	int _tmp2__size;
	int _tmp2__length1;
	GVariantIter _tmp3_;
	GVariant* _tmp4_;
	guint _vala_matches;
	GVariant* _tmp5_;
	_reply_message = g_dbus_connection_send_message_with_reply_finish (g_dbus_proxy_get_connection ((GDBusProxy *) self), g_simple_async_result_get_op_res_gpointer ((GSimpleAsyncResult *) _res_), error);
	if (!_reply_message) {
		return;
	}
	if (g_dbus_message_to_gerror (_reply_message, error)) {
		g_object_unref (_reply_message);
		return;
	}
	_reply = g_dbus_message_get_body (_reply_message);
	g_variant_iter_init (&_reply_iter, _reply);
	_vala_events = g_variant_iter_next_value (&_reply_iter);
	*events = _vala_events;
	_vala_relevancies_length1 = 0;
	_tmp1_ = g_variant_iter_next_value (&_reply_iter);
	_tmp2_ = g_new (gdouble, 5);
	_tmp2__length = 0;
	_tmp2__size = 4;
	_tmp2__length1 = 0;
	g_variant_iter_init (&_tmp3_, _tmp1_);
	for (; (_tmp4_ = g_variant_iter_next_value (&_tmp3_)) != NULL; _tmp2__length1++) {
		if (_tmp2__size == _tmp2__length) {
			_tmp2__size = 2 * _tmp2__size;
			_tmp2_ = g_renew (gdouble, _tmp2_, _tmp2__size + 1);
		}
		_tmp2_[_tmp2__length++] = g_variant_get_double (_tmp4_);
		g_variant_unref (_tmp4_);
	}
	_vala_relevancies_length1 = _tmp2__length1;
	_vala_relevancies = _tmp2_;
	g_variant_unref (_tmp1_);
	*relevancies = _vala_relevancies;
	*relevancies_length1 = _vala_relevancies_length1;
	_tmp5_ = g_variant_iter_next_value (&_reply_iter);
	_vala_matches = g_variant_get_uint32 (_tmp5_);
	g_variant_unref (_tmp5_);
	*matches = _vala_matches;
	g_object_unref (_reply_message);
}
