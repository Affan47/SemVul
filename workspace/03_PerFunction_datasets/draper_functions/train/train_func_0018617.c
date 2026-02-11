string_to_utf8 (const char* self, int* result_length1) {
	gchar* result = NULL;
	gchar* _tmp1_;
	gint __result__size_;
	gint _result__length1;
	gint _tmp0_;
	gchar* _result_;
	gchar* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	_result_ = (_tmp1_ = g_new0 (gchar, _tmp0_ = strlen (self) + 1), _result__length1 = _tmp0_, __result__size_ = _result__length1, _tmp1_);
	_result__length1--;
	memcpy (_result_, self, strlen (self));
	result = (_tmp2_ = _result_, *result_length1 = _result__length1, _tmp2_);
	return result;
	_result_ = (g_free (_result_), NULL);
}
