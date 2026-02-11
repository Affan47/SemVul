keyfile_from_stdin (GError** error) {
	GKeyFile* result = NULL;
	const gchar* tmp = NULL;
	gchar buffer[1024] = {0};
	GString* s = NULL;
	GString* _tmp0_ = NULL;
	GKeyFile* kf = NULL;
	GKeyFile* _tmp6_ = NULL;
	GString* _tmp7_ = NULL;
	const gchar* _tmp8_ = NULL;
	GString* _tmp9_ = NULL;
	gssize _tmp10_ = 0L;
	GError * _inner_error_ = NULL;
	_tmp0_ = g_string_new ("");
	s = _tmp0_;
	while (TRUE) {
		FILE* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		GString* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		_tmp1_ = stdin;
		_tmp2_ = fgets (buffer, 1024, _tmp1_);
		tmp = _tmp2_;
		_tmp3_ = tmp;
		if (!(_tmp3_ != NULL)) {
			break;
		}
		_tmp4_ = s;
		_tmp5_ = tmp;
		g_string_append (_tmp4_, _tmp5_);
	}
	_tmp6_ = g_key_file_new ();
	kf = _tmp6_;
	_tmp7_ = s;
	_tmp8_ = _tmp7_->str;
	_tmp9_ = s;
	_tmp10_ = _tmp9_->len;
	g_key_file_load_from_data (kf, _tmp8_, (gsize) _tmp10_, 0, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_g_key_file_free0 (kf);
		_g_string_free0 (s);
		return NULL;
	}
	result = kf;
	_g_string_free0 (s);
	return result;
}
