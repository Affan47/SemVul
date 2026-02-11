ti_calypso_percent_em23_fillArray (TiCalypsoPercentEM23* self, gint** array, int* array_length1, gint v1, gint v2, gint v3, gint v4, gint v5, gint v6) {
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	gint _tmp5_ = 0;
	gint* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = v1;
	_tmp1_ = v2;
	_tmp2_ = v3;
	_tmp3_ = v4;
	_tmp4_ = v5;
	_tmp5_ = v6;
	_tmp6_ = g_new0 (gint, 6);
	_tmp6_[0] = _tmp0_;
	_tmp6_[1] = _tmp1_;
	_tmp6_[2] = _tmp2_;
	_tmp6_[3] = _tmp3_;
	_tmp6_[4] = _tmp4_;
	_tmp6_[5] = _tmp5_;
	*array = (g_free (*array), NULL);
	*array = _tmp6_;
	*array_length1 = 6;
}
