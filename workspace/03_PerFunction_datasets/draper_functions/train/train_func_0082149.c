alm_utilities_parse_negation (gchar** val) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (*val != NULL, FALSE);
	_tmp0_ = *val;
	_tmp1_ = g_str_has_prefix (_tmp0_, "!");
	if (!_tmp1_) {
		result = FALSE;
		return result;
	}
	_tmp2_ = *val;
	_tmp3_ = string_substring (_tmp2_, (glong) 1, (glong) (-1));
	_g_free0 (*val);
	*val = _tmp3_;
	result = TRUE;
	return result;
}
