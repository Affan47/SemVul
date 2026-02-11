utils_key_file_get_bool (GKeyFile* kf, const gchar* group, const gchar* key, gboolean def_val) {
	gboolean result = FALSE;
	gboolean val = FALSE;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (kf != NULL, FALSE);
	g_return_val_if_fail (group != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	{
		GKeyFile* _tmp0_;
		const gchar* _tmp1_;
		const gchar* _tmp2_;
		gboolean _tmp3_ = FALSE;
		gboolean _tmp4_;
		_tmp0_ = kf;
		_tmp1_ = group;
		_tmp2_ = key;
		_tmp3_ = g_key_file_get_boolean (_tmp0_, _tmp1_, _tmp2_, &_inner_error_);
		_tmp4_ = _tmp3_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_KEY_FILE_ERROR) {
				goto __catch9_g_key_file_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return FALSE;
		}
		val = _tmp4_;
	}
	goto __finally9;
	__catch9_g_key_file_error:
	{
		GError* err = NULL;
		gboolean _tmp5_;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp5_ = def_val;
		val = _tmp5_;
		_g_error_free0 (err);
	}
	__finally9:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	result = val;
	return result;
}
