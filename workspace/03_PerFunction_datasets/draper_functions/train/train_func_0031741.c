free_smartphone_data_world_country_init (FreeSmartphoneDataWorldCountry *self, const gchar* code, const gchar* name) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_if_fail (code != NULL);
	g_return_if_fail (name != NULL);
	memset (self, 0, sizeof (FreeSmartphoneDataWorldCountry));
	_tmp0_ = code;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 ((*self).code);
	(*self).code = _tmp1_;
	_tmp2_ = name;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 ((*self).name);
	(*self).name = _tmp3_;
}
