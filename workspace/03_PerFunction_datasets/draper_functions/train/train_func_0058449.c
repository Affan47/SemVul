__lambda11_ (Block7Data* _data7_, GIsiCommErrorCode err, guint8 cur, guint8 tgt) {
	NokiaIsiIsiDeviceSetFunctionality * self;
	GIsiCommErrorCode _tmp0_ = 0;
	self = _data7_->self;
	_tmp0_ = err;
	if (_tmp0_ == GISI_COMM_ERROR_CODE_OK) {
		NokiaIsiModem* _tmp1_ = NULL;
		guint8 _tmp2_ = 0;
		gchar* _tmp3_ = NULL;
		FsoGsmModem* _tmp4_ = NULL;
		FsoGsmModem* _tmp5_ = NULL;
		FsoFrameworkLogger* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		gchar* _tmp9_ = NULL;
		gchar* _tmp10_ = NULL;
		_tmp1_ = nokia_isi_modem;
		_tmp2_ = cur;
		_tmp3_ = nokia_isi_modem_deviceFunctionalityModemStateToString (_tmp1_, _tmp2_);
		_g_free0 (_data7_->curlevel);
		_data7_->curlevel = _tmp3_;
		_tmp4_ = fso_gsm_abstract_mediator_get_modem ((FsoGsmAbstractMediator*) self);
		_tmp5_ = _tmp4_;
		_tmp6_ = ((FsoFrameworkAbstractObject*) _tmp5_)->logger;
		_tmp7_ = _data7_->curlevel;
		_tmp8_ = string_to_string (_tmp7_);
		_tmp9_ = g_strconcat ("current level is ", _tmp8_, NULL);
		_tmp10_ = _tmp9_;
		fso_framework_logger_debug (_tmp6_, _tmp10_);
		_g_free0 (_tmp10_);
	}
	nokia_isi_isi_device_set_functionality_real_run_co (_data7_->_async_data_);
}
