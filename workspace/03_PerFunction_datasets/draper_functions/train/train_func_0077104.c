number_pwr (Number* self, Number* y) {
	Number* result = NULL;
	gboolean _tmp0_ = FALSE;
	Number* _tmp5_ = NULL;
	gboolean _tmp6_ = FALSE;
	Number* _tmp8_ = NULL;
	Number* _tmp9_ = NULL;
	Number* _tmp10_ = NULL;
	Number* _tmp11_ = NULL;
	Number* _tmp12_ = NULL;
	Number* _tmp13_ = NULL;
	Number* _tmp14_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (y != NULL, NULL);
	_tmp0_ = number_is_zero (self);
	if (_tmp0_) {
		Number* _tmp1_ = NULL;
		gint _tmp2_ = 0;
		Number* _tmp4_ = NULL;
		_tmp1_ = y;
		_tmp2_ = _tmp1_->re_sign;
		if (_tmp2_ < 0) {
			const gchar* _tmp3_ = NULL;
			_tmp3_ = _ ("The power of zero is undefined for a negative exponent");
			mperr (_tmp3_);
		}
		_tmp4_ = number_new_integer ((gint64) 0);
		result = _tmp4_;
		return result;
	}
	_tmp5_ = y;
	_tmp6_ = number_is_zero (_tmp5_);
	if (_tmp6_) {
		Number* _tmp7_ = NULL;
		_tmp7_ = number_new_integer ((gint64) 1);
		result = _tmp7_;
		return result;
	}
	_tmp8_ = y;
	_tmp9_ = number_ln (self);
	_tmp10_ = _tmp9_;
	_tmp11_ = number_multiply (_tmp8_, _tmp10_);
	_tmp12_ = _tmp11_;
	_tmp13_ = number_epowy (_tmp12_);
	_tmp14_ = _tmp13_;
	_number_unref0 (_tmp12_);
	_number_unref0 (_tmp10_);
	result = _tmp14_;
	return result;
}
