skk_util_get_okurigana_prefix_for_char (gunichar uc) {
	gchar* result = NULL;
	gunichar _tmp0_;
	_tmp0_ = uc;
	if (_tmp0_ == 12435U) {
		gchar* _tmp1_;
		_tmp1_ = g_strdup ("n");
		result = _tmp1_;
		return result;
	} else {
		gboolean _tmp2_ = FALSE;
		gunichar _tmp3_;
		gboolean _tmp5_;
		_tmp3_ = uc;
		if (_tmp3_ < 12353U) {
			_tmp2_ = TRUE;
		} else {
			gunichar _tmp4_;
			_tmp4_ = uc;
			_tmp2_ = _tmp4_ > 12435U;
		}
		_tmp5_ = _tmp2_;
		if (_tmp5_) {
			result = NULL;
			return result;
		} else {
			gunichar _tmp6_;
			const gchar* _tmp7_;
			gchar* _tmp8_;
			_tmp6_ = uc;
			_tmp7_ = SKK_UTIL_KanaRomTable[_tmp6_ - 12353U];
			_tmp8_ = g_strdup (_tmp7_);
			result = _tmp8_;
			return result;
		}
	}
}
