double_string (gdouble x) {
	gchar* result = NULL;
	gdouble _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* value;
	const gchar* _tmp2_;
	_tmp0_ = x;
	_tmp1_ = g_strdup_printf ("%.6f", _tmp0_);
	value = _tmp1_;
	_tmp2_ = value;
	if (g_strcmp0 (_tmp2_, "-0.000000") == 0) {
		gchar* _tmp3_;
		_tmp3_ = g_strdup ("0.000000");
		result = _tmp3_;
		_g_free0 (value);
		return result;
	} else {
		result = value;
		return result;
	}
	_g_free0 (value);
}
