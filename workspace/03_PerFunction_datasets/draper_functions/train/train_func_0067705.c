fso_gsm_constants_phonenumberTupleToString (const gchar* number, gint ntype) {
	gchar* result = NULL;
	gint _tmp0_ = 0;
	g_return_val_if_fail (number != NULL, NULL);
	_tmp0_ = ntype;
	if (_tmp0_ == 145) {
		const gchar* _tmp1_ = NULL;
		gchar _tmp2_ = '\0';
		_tmp1_ = number;
		_tmp2_ = string_get (_tmp1_, (glong) 0);
		if (_tmp2_ == '+') {
			const gchar* _tmp3_ = NULL;
			gchar* _tmp4_ = NULL;
			_tmp3_ = number;
			_tmp4_ = g_strdup (_tmp3_);
			result = _tmp4_;
			return result;
		} else {
			const gchar* _tmp5_ = NULL;
			gchar* _tmp6_ = NULL;
			_tmp5_ = number;
			_tmp6_ = g_strdup_printf ("+%s", _tmp5_);
			result = _tmp6_;
			return result;
		}
	} else {
		const gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		_tmp7_ = number;
		_tmp8_ = g_strdup (_tmp7_);
		result = _tmp8_;
		return result;
	}
}
