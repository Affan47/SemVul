abraca_configurable_register (AbracaIConfigurable* obj) {
	GKeyFile* file = NULL;
	gboolean _tmp0_;
	AbracaIConfigurable* _tmp5_;
	AbracaIConfigurable* _tmp6_;
	AbracaIConfigurable* _tmp7_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (obj != NULL);
	_tmp0_ = abraca_configurable_config_loaded;
	if (_tmp0_) {
		GKeyFile* _tmp1_ = NULL;
		_tmp1_ = abraca_configurable_read_config ();
		_g_key_file_free0 (file);
		file = _tmp1_;
		{
			AbracaIConfigurable* _tmp2_;
			GKeyFile* _tmp3_;
			_tmp2_ = obj;
			_tmp3_ = file;
			abraca_iconfigurable_set_configuration (_tmp2_, _tmp3_, &_inner_error_);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == G_KEY_FILE_ERROR) {
					goto __catch13_g_key_file_error;
				}
				_g_key_file_free0 (file);
				g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return;
			}
		}
		goto __finally13;
		__catch13_g_key_file_error:
		{
			GError* e = NULL;
			const gchar* _tmp4_;
			e = _inner_error_;
			_inner_error_ = NULL;
			_tmp4_ = e->message;
			g_error ("configurable.vala:47: %s", _tmp4_);
			_g_error_free0 (e);
		}
		__finally13:
		if (_inner_error_ != NULL) {
			_g_key_file_free0 (file);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp5_ = obj;
	abraca_configurable_configurables = g_slist_remove (abraca_configurable_configurables, _tmp5_);
	_tmp6_ = obj;
	_tmp7_ = _g_object_ref0 (_tmp6_);
	abraca_configurable_configurables = g_slist_prepend (abraca_configurable_configurables, _tmp7_);
	_g_key_file_free0 (file);
}
