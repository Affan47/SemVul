fso_gsm_constants_determinePhoneNumberType (const gchar* number) {
	guint8 result = 0U;
	gint _tmp0_ = 0;
	const gchar* _tmp1_ = NULL;
	gchar _tmp2_ = '\0';
	gint _tmp3_ = 0;
	g_return_val_if_fail (number != NULL, 0U);
	_tmp1_ = number;
	_tmp2_ = string_get (_tmp1_, (glong) 0);
	if (_tmp2_ == '+') {
		_tmp0_ = 145;
	} else {
		_tmp0_ = 129;
	}
	_tmp3_ = _tmp0_;
	result = (guint8) _tmp3_;
	return result;
}
