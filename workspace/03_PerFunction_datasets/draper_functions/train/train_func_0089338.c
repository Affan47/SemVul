__lambda26_ (Block5Data* _data5_, GIsiCommErrorCode _error_, guint8* answer, int answer_length1) {
	NokiaIsiIsiDebugCommand * self;
	GIsiCommErrorCode _tmp0_ = 0;
	self = _data5_->self;
	_tmp0_ = _error_;
	if (_tmp0_ == GISI_COMM_ERROR_CODE_OK) {
		guint8* _tmp1_ = NULL;
		gint _tmp1__length1 = 0;
		gchar* _tmp2_ = NULL;
		gchar* _tmp3_ = NULL;
		_tmp1_ = answer;
		_tmp1__length1 = answer_length1;
		_tmp2_ = fso_framework_string_handling_hexdump (_tmp1_, _tmp1__length1, 16, "", (guchar) '?');
		_tmp3_ = _tmp2_;
		fso_gsm_debug_command_set_response ((FsoGsmDebugCommand*) self, _tmp3_);
		_g_free0 (_tmp3_);
	} else {
		fso_gsm_debug_command_set_response ((FsoGsmDebugCommand*) self, "<ISI COMMUNICATION ERROR>");
	}
	nokia_isi_isi_debug_command_real_run_co (_data5_->_async_data_);
}
