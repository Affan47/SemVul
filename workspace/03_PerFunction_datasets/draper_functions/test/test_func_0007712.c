_dbus_unity_protocol_scope_service_push_results (UnityProtocolScopeService* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GVariantIter _arguments_iter;
	gchar* channel_id = NULL;
	GVariant* _tmp110_;
	gchar* search_string = NULL;
	GVariant* _tmp111_;
	gchar* source_scope_id = NULL;
	GVariant* _tmp112_;
	GVariant* result_variant = NULL;
	GVariant* _tmp113_;
	gchar** categories = NULL;
	int categories_length1 = 0;
	GVariant* _tmp114_;
	gchar** _tmp115_;
	int _tmp115__length;
	int _tmp115__size;
	int _tmp115__length1;
	GVariantIter _tmp116_;
	GVariant* _tmp117_;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp110_ = g_variant_iter_next_value (&_arguments_iter);
	channel_id = g_variant_dup_string (_tmp110_, NULL);
	g_variant_unref (_tmp110_);
	_tmp111_ = g_variant_iter_next_value (&_arguments_iter);
	search_string = g_variant_dup_string (_tmp111_, NULL);
	g_variant_unref (_tmp111_);
	_tmp112_ = g_variant_iter_next_value (&_arguments_iter);
	source_scope_id = g_variant_dup_string (_tmp112_, NULL);
	g_variant_unref (_tmp112_);
	_tmp113_ = g_variant_iter_next_value (&_arguments_iter);
	result_variant = g_variant_get_variant (_tmp113_);
	g_variant_unref (_tmp113_);
	_tmp114_ = g_variant_iter_next_value (&_arguments_iter);
	_tmp115_ = g_new (gchar*, 5);
	_tmp115__length = 0;
	_tmp115__size = 4;
	_tmp115__length1 = 0;
	g_variant_iter_init (&_tmp116_, _tmp114_);
	for (; (_tmp117_ = g_variant_iter_next_value (&_tmp116_)) != NULL; _tmp115__length1++) {
		if (_tmp115__size == _tmp115__length) {
			_tmp115__size = 2 * _tmp115__size;
			_tmp115_ = g_renew (gchar*, _tmp115_, _tmp115__size + 1);
		}
		_tmp115_[_tmp115__length++] = g_variant_dup_string (_tmp117_, NULL);
		g_variant_unref (_tmp117_);
	}
	categories_length1 = _tmp115__length1;
	_tmp115_[_tmp115__length] = NULL;
	categories = _tmp115_;
	g_variant_unref (_tmp114_);
	unity_protocol_scope_service_push_results (self, channel_id, search_string, source_scope_id, result_variant, categories, categories_length1, NULL, (GAsyncReadyCallback) _dbus_unity_protocol_scope_service_push_results_ready, invocation);
	_g_free0 (channel_id);
	_g_free0 (search_string);
	_g_free0 (source_scope_id);
	_g_variant_unref0 (result_variant);
	categories = (_vala_array_free (categories, categories_length1, (GDestroyNotify) g_free), NULL);
}
