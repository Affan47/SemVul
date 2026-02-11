fso_gsm_plus_cscb_issue (FsoGsmPlusCSCB* self, FsoGsmPlusCSCBMode m) {
	gchar* result = NULL;
	gint _tmp0_ = 0;
	FsoGsmPlusCSCBMode _tmp1_ = 0;
	gint _tmp2_ = 0;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1_ = m;
	if (_tmp1_ == FSO_GSM_PLUS_CSCB_MODE_NONE) {
		_tmp0_ = 0;
	} else {
		_tmp0_ = 1;
	}
	_tmp2_ = _tmp0_;
	_tmp3_ = g_strdup_printf ("+CSCB=%u,\"\",\"\"", (guint) _tmp2_);
	result = _tmp3_;
	return result;
}
