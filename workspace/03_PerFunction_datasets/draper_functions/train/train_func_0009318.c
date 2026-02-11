cc_credentials_login_capture_on_bus_acquired (CcCredentialsLoginCapture* self, GDBusConnection* conn) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (conn != NULL);
	{
		GDBusConnection* _tmp0_ = NULL;
		_tmp0_ = conn;
		cc_credentials_login_capture_register_object (self, _tmp0_, "/com/canonical/webcredentials/capture", &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch9_g_io_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	goto __finally9;
	__catch9_g_io_error:
	{
		GError* e = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("cc-credentials-login-capture.vala:61: Could not register service.");
		_g_error_free0 (e);
	}
	__finally9:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
