test_lookup_no_name (void) {
	GError * _inner_error_ = NULL;
	{
		gchar* password = NULL;
		SecretSchema* _tmp0_ = NULL;
		gchar* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		gchar* _tmp3_ = NULL;
		SecretSchema* _tmp4_ = NULL;
		gchar* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		_tmp0_ = schema;
		_tmp1_ = secret_password_lookup_sync (_tmp0_, NULL, &_inner_error_, "number", 5, NULL);
		password = _tmp1_;
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
		}
		_tmp2_ = password;
		_vala_assert (_tmp2_ == NULL, "password == null");
		_tmp4_ = no_name_schema;
		_tmp5_ = secret_password_lookup_sync (_tmp4_, NULL, &_inner_error_, "number", 5, NULL);
		_tmp3_ = _tmp5_;
		if (_inner_error_ != NULL) {
			_g_free0 (password);
			goto __catch2_g_error;
		}
		_g_free0 (password);
		password = _tmp3_;
		_tmp6_ = password;
		_vala_assert (g_strcmp0 (_tmp6_, "555") == 0, "password == \"555\"");
		_g_free0 (password);
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError* e = NULL;
		const gchar* _tmp7_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp7_ = e->message;
		g_error ("test-vala-lang.vala:49: %s", _tmp7_);
		_g_error_free0 (e);
	}
	__finally2:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
