_dbus_boxes_search_provider_GetSubsearchResultSet (BoxesSearchProvider* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GVariantIter _arguments_iter;
	gchar** previous_results = NULL;
	int previous_results_length1 = 0;
	GVariant* _tmp7_;
	gchar** _tmp8_;
	int _tmp8__length;
	int _tmp8__size;
	int _tmp8__length1;
	GVariantIter _tmp9_;
	GVariant* _tmp10_;
	gchar** new_terms = NULL;
	int new_terms_length1 = 0;
	GVariant* _tmp11_;
	gchar** _tmp12_;
	int _tmp12__length;
	int _tmp12__size;
	int _tmp12__length1;
	GVariantIter _tmp13_;
	GVariant* _tmp14_;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp7_ = g_variant_iter_next_value (&_arguments_iter);
	_tmp8_ = g_new (gchar*, 5);
	_tmp8__length = 0;
	_tmp8__size = 4;
	_tmp8__length1 = 0;
	g_variant_iter_init (&_tmp9_, _tmp7_);
	for (; (_tmp10_ = g_variant_iter_next_value (&_tmp9_)) != NULL; _tmp8__length1++) {
		if (_tmp8__size == _tmp8__length) {
			_tmp8__size = 2 * _tmp8__size;
			_tmp8_ = g_renew (gchar*, _tmp8_, _tmp8__size + 1);
		}
		_tmp8_[_tmp8__length++] = g_variant_dup_string (_tmp10_, NULL);
		g_variant_unref (_tmp10_);
	}
	previous_results_length1 = _tmp8__length1;
	_tmp8_[_tmp8__length] = NULL;
	previous_results = _tmp8_;
	g_variant_unref (_tmp7_);
	_tmp11_ = g_variant_iter_next_value (&_arguments_iter);
	_tmp12_ = g_new (gchar*, 5);
	_tmp12__length = 0;
	_tmp12__size = 4;
	_tmp12__length1 = 0;
	g_variant_iter_init (&_tmp13_, _tmp11_);
	for (; (_tmp14_ = g_variant_iter_next_value (&_tmp13_)) != NULL; _tmp12__length1++) {
		if (_tmp12__size == _tmp12__length) {
			_tmp12__size = 2 * _tmp12__size;
			_tmp12_ = g_renew (gchar*, _tmp12_, _tmp12__size + 1);
		}
		_tmp12_[_tmp12__length++] = g_variant_dup_string (_tmp14_, NULL);
		g_variant_unref (_tmp14_);
	}
	new_terms_length1 = _tmp12__length1;
	_tmp12_[_tmp12__length] = NULL;
	new_terms = _tmp12_;
	g_variant_unref (_tmp11_);
	boxes_search_provider_GetSubsearchResultSet (self, previous_results, previous_results_length1, new_terms, new_terms_length1, (GAsyncReadyCallback) _dbus_boxes_search_provider_GetSubsearchResultSet_ready, invocation);
	previous_results = (_vala_array_free (previous_results, previous_results_length1, (GDestroyNotify) g_free), NULL);
	new_terms = (_vala_array_free (new_terms, new_terms_length1, (GDestroyNotify) g_free), NULL);
}
