umockdev_in_mock_environment (void) {
	gboolean result = FALSE;
	gchar* preload = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	_tmp0_ = g_getenv ("LD_PRELOAD");
	_tmp1_ = g_strdup (_tmp0_);
	preload = _tmp1_;
	_tmp2_ = preload;
	if (_tmp2_ == NULL) {
		result = FALSE;
		_g_free0 (preload);
		return result;
	}
	_tmp3_ = preload;
	_tmp4_ = string_contains (_tmp3_, "libumockdev-preload");
	result = _tmp4_;
	_g_free0 (preload);
	return result;
}
