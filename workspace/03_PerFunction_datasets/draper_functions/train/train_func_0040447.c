_dbus_cc_webcredentials_indicator_get_failures (CcWebcredentialsIndicator* self) {
	guint* result;
	int result_length1 = 0;
	guint* _tmp28_;
	GVariantBuilder _tmp29_;
	int _tmp30_;
	GVariant* _reply;
	result = cc_webcredentials_indicator_get_failures (self, &result_length1);
	_tmp28_ = result;
	g_variant_builder_init (&_tmp29_, G_VARIANT_TYPE ("au"));
	for (_tmp30_ = 0; _tmp30_ < result_length1; _tmp30_++) {
		g_variant_builder_add_value (&_tmp29_, g_variant_new_uint32 (*_tmp28_));
		_tmp28_++;
	}
	_reply = g_variant_builder_end (&_tmp29_);
	result = (g_free (result), NULL);
	return _reply;
}
