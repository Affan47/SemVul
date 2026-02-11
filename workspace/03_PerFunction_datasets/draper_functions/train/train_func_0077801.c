click_try_chown (const gchar* path, struct passwd* pw, GError** error) {
	const gchar* _tmp0_ = NULL;
	struct passwd* _tmp1_ = NULL;
	uid_t _tmp2_ = {0};
	struct passwd* _tmp3_ = NULL;
	gid_t _tmp4_ = {0};
	gint _tmp5_ = 0;
	GError * _inner_error_ = NULL;
	g_return_if_fail (path != NULL);
	g_return_if_fail (pw != NULL);
	_tmp0_ = path;
	_tmp1_ = pw;
	_tmp2_ = _tmp1_->pw_uid;
	_tmp3_ = pw;
	_tmp4_ = _tmp3_->pw_gid;
	_tmp5_ = chown (_tmp0_, _tmp2_, _tmp4_);
	if (_tmp5_ < 0) {
		const gchar* _tmp6_ = NULL;
		gint _tmp7_ = 0;
		const gchar* _tmp8_ = NULL;
		GError* _tmp9_ = NULL;
		_tmp6_ = path;
		_tmp7_ = errno;
		_tmp8_ = g_strerror (_tmp7_);
		_tmp9_ = g_error_new (CLICK_USER_ERROR, CLICK_USER_ERROR_CHOWN_DB, "Cannot set ownership of database directory %s: %s", _tmp6_, _tmp8_);
		_inner_error_ = _tmp9_;
		if (_inner_error_->domain == CLICK_USER_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
