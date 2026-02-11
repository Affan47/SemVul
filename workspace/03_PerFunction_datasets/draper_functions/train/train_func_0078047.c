auth_accounts_load (AuthAccounts* self) {
	GError * _inner_error_;
	char* pino_dir;
	GFile* dir;
	GFile* _tmp0_;
	char* _tmp1_;
	GFile* acc_file;
	char* content;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	pino_dir = g_strconcat (g_get_user_config_dir (), "/lekhonee-gnome", NULL);
	dir = g_file_new_for_path (pino_dir);
	if (!g_file_query_exists (dir, NULL)) {
		g_file_make_directory (dir, NULL, &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_free0 (pino_dir);
			_g_object_unref0 (dir);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	dir = (_tmp0_ = NULL, _g_object_unref0 (dir), _tmp0_);
	self->priv->acc_file_path = (_tmp1_ = g_strconcat (pino_dir, "/accounts.xml", NULL), _g_free0 (self->priv->acc_file_path), _tmp1_);
	acc_file = g_file_new_for_path (self->priv->acc_file_path);
	if (!g_file_query_exists (acc_file, NULL)) {
		self->is_new = TRUE;
		_g_free0 (pino_dir);
		_g_object_unref0 (dir);
		_g_object_unref0 (acc_file);
		return;
	}
	content = NULL;
	{
		GFileInputStream* _tmp2_;
		GFileInputStream* _tmp3_;
		GDataInputStream* _tmp4_;
		GDataInputStream* stream;
		char* _tmp5_;
		char* _tmp6_;
		_tmp2_ = g_file_read (acc_file, NULL, &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_free0 (pino_dir);
			_g_object_unref0 (dir);
			_g_object_unref0 (acc_file);
			_g_free0 (content);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		stream = (_tmp4_ = g_data_input_stream_new ((GInputStream*) (_tmp3_ = _tmp2_)), _g_object_unref0 (_tmp3_), _tmp4_);
		_tmp5_ = g_data_input_stream_read_until (stream, "", NULL, NULL, &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_object_unref0 (stream);
			_g_free0 (pino_dir);
			_g_object_unref0 (dir);
			_g_object_unref0 (acc_file);
			_g_free0 (content);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		content = (_tmp6_ = _tmp5_, _g_free0 (content), _tmp6_);
		_g_object_unref0 (stream);
	}
	auth_accounts_parse (self, content);
	_g_free0 (pino_dir);
	_g_object_unref0 (dir);
	_g_object_unref0 (acc_file);
	_g_free0 (content);
}
