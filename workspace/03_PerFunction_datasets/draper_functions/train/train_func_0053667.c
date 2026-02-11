fso_gsm_plus_cpwd_issue (FsoGsmPlusCPWD* self, const gchar* facility, const gchar* p1, const gchar* p2) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (facility != NULL, NULL);
	g_return_val_if_fail (p1 != NULL, NULL);
	g_return_val_if_fail (p2 != NULL, NULL);
	_tmp0_ = facility;
	_tmp1_ = string_to_string (_tmp0_);
	_tmp2_ = p1;
	_tmp3_ = string_to_string (_tmp2_);
	_tmp4_ = p2;
	_tmp5_ = string_to_string (_tmp4_);
	_tmp6_ = g_strconcat ("+CPWD=\"", _tmp1_, "\",\"", _tmp3_, "\",\"", _tmp5_, "\"", NULL);
	result = _tmp6_;
	return result;
}
