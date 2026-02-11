dvb_settings_get_string (DVBSettings* self, const gchar* group_name, const gchar* key, GError** error) {
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	GKeyFile* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (group_name != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	_tmp1_ = self->priv->keyfile;
	_tmp2_ = group_name;
	_tmp3_ = key;
	_tmp4_ = g_key_file_get_string (_tmp1_, _tmp2_, _tmp3_, &_inner_error_);
	_tmp0_ = _tmp4_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == G_KEY_FILE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	result = _tmp0_;
	return result;
}
