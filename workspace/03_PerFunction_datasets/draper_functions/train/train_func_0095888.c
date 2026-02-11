fso_gsm_sms_storage_factory_create (const gchar* type, const gchar* imsi) {
	FsoGsmISmsStorage* result = NULL;
	FsoGsmISmsStorage* storage = NULL;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GQuark _tmp3_ = 0U;
	static GQuark _tmp2_label0 = 0;
	g_return_val_if_fail (type != NULL, NULL);
	g_return_val_if_fail (imsi != NULL, NULL);
	storage = NULL;
	_tmp0_ = type;
	_tmp1_ = _tmp0_;
	_tmp3_ = (NULL == _tmp1_) ? 0 : g_quark_from_string (_tmp1_);
	if (_tmp3_ == ((0 != _tmp2_label0) ? _tmp2_label0 : (_tmp2_label0 = g_quark_from_static_string ("default")))) {
		switch (0) {
			default:
			{
				const gchar* _tmp4_ = NULL;
				FsoGsmSmsStorage* _tmp5_ = NULL;
				_tmp4_ = imsi;
				_tmp5_ = fso_gsm_sms_storage_new (_tmp4_);
				_g_object_unref0 (storage);
				storage = (FsoGsmISmsStorage*) _tmp5_;
				break;
			}
		}
	} else {
		switch (0) {
			default:
			{
				FsoGsmNullSmsStorage* _tmp6_ = NULL;
				_tmp6_ = fso_gsm_null_sms_storage_new ();
				_g_object_unref0 (storage);
				storage = (FsoGsmISmsStorage*) _tmp6_;
				break;
			}
		}
	}
	result = storage;
	return result;
}
