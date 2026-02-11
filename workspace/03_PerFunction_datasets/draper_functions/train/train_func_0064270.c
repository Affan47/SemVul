test_read_alias (void) {
	GError * _inner_error_ = NULL;
	{
		SecretService* service = NULL;
		SecretService* _tmp0_ = NULL;
		gchar* path = NULL;
		SecretService* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		_tmp0_ = secret_service_get_sync (SECRET_SERVICE_NONE, NULL, &_inner_error_);
		service = _tmp0_;
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp1_ = service;
		_tmp2_ = secret_service_read_alias_dbus_path_sync (_tmp1_, "default", NULL, &_inner_error_);
		path = _tmp2_;
		if (_inner_error_ != NULL) {
			_g_object_unref0 (service);
			goto __catch0_g_error;
		}
		_tmp3_ = path;
		_vala_assert (_tmp3_ != NULL, "path != null");
		_g_free0 (path);
		_g_object_unref0 (service);
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError* e = NULL;
		const gchar* _tmp4_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp4_ = e->message;
		g_error ("test-vala-unstable.vala:18: %s", _tmp4_);
		_g_error_free0 (e);
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
