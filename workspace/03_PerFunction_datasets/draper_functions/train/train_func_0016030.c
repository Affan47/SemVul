click_hook_priv_drop_failure (ClickHook* self, const gchar* name, GError** error) {
	const gchar* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	const gchar* _tmp2_ = NULL;
	GError* _tmp3_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	_tmp0_ = name;
	_tmp1_ = errno;
	_tmp2_ = g_strerror (_tmp1_);
	_tmp3_ = g_error_new (CLICK_HOOKS_ERROR, CLICK_HOOKS_ERROR_DROP_PRIVS, "Cannot drop privileges (%s): %s", _tmp0_, _tmp2_);
	_inner_error_ = _tmp3_;
	if (_inner_error_->domain == CLICK_HOOKS_ERROR) {
		g_propagate_error (error, _inner_error_);
		return;
	} else {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
