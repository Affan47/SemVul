fso_gsm_v250_d_issue (FsoGsmV250D* self, const gchar* number, gboolean voice) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gchar* postfix = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar* safenumber = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	const gchar* _tmp7_ = NULL;
	gchar* _tmp8_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (number != NULL, NULL);
	_tmp1_ = voice;
	if (_tmp1_) {
		_tmp0_ = ";";
	} else {
		_tmp0_ = "";
	}
	_tmp2_ = _tmp0_;
	_tmp3_ = g_strdup (_tmp2_);
	postfix = _tmp3_;
	_tmp4_ = number;
	_tmp5_ = fso_gsm_constants_cleanPhoneNumber (_tmp4_);
	safenumber = _tmp5_;
	_tmp6_ = string_to_string (safenumber);
	_tmp7_ = string_to_string (postfix);
	_tmp8_ = g_strconcat ("D", _tmp6_, _tmp7_, NULL);
	result = _tmp8_;
	_g_free0 (safenumber);
	_g_free0 (postfix);
	return result;
}
