libisocodes_iso_3166_2_real__get_fields (libisocodesISO_Codes* base, int* result_length1) {
	libisocodesISO_3166_2 * self;
	gchar** result = NULL;
	gchar* _tmp0_;
	gchar* _tmp1_;
	gchar* _tmp2_;
	gchar** _tmp3_ = NULL;
	gchar** _tmp4_;
	gint _tmp4__length1;
	self = (libisocodesISO_3166_2*) base;
	_tmp0_ = g_strdup ("code");
	_tmp1_ = g_strdup ("parent");
	_tmp2_ = g_strdup ("name");
	_tmp3_ = g_new0 (gchar*, 3 + 1);
	_tmp3_[0] = _tmp0_;
	_tmp3_[1] = _tmp1_;
	_tmp3_[2] = _tmp2_;
	_tmp4_ = _tmp3_;
	_tmp4__length1 = 3;
	if (result_length1) {
		*result_length1 = _tmp4__length1;
	}
	result = _tmp4_;
	return result;
}
