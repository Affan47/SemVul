fso_framework_abstract_logger_real_format (FsoFrameworkAbstractLogger* self, const gchar* message, const gchar* level) {
	gchar* result = NULL;
	GTimeVal t = {0};
	gchar* _tmp0_ = NULL;
	ReprDelegate _tmp1_ = NULL;
	void* _tmp1__target = NULL;
	gchar* repr = NULL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* str = NULL;
	gchar* _tmp7_ = NULL;
	gchar* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	const gchar* _tmp10_ = NULL;
	const gchar* _tmp11_ = NULL;
	const gchar* _tmp12_ = NULL;
	gchar* _tmp13_ = NULL;
	gchar* _tmp14_ = NULL;
	gchar* _tmp15_ = NULL;
	gboolean _tmp16_ = FALSE;
	g_return_val_if_fail (message != NULL, NULL);
	g_return_val_if_fail (level != NULL, NULL);
	g_get_current_time (&t);
	_tmp1_ = self->reprdelegate;
	_tmp1__target = self->reprdelegate_target;
	if (_tmp1_ != NULL) {
		ReprDelegate _tmp2_ = NULL;
		void* _tmp2__target = NULL;
		gchar* _tmp3_ = NULL;
		_tmp2_ = self->reprdelegate;
		_tmp2__target = self->reprdelegate_target;
		_tmp3_ = _tmp2_ (_tmp2__target);
		_g_free0 (_tmp0_);
		_tmp0_ = _tmp3_;
	} else {
		gchar* _tmp4_ = NULL;
		_tmp4_ = g_strdup ("");
		_g_free0 (_tmp0_);
		_tmp0_ = _tmp4_;
	}
	_tmp5_ = _tmp0_;
	_tmp6_ = g_strdup (_tmp5_);
	repr = _tmp6_;
	_tmp7_ = g_time_val_to_iso8601 (&t);
	_tmp8_ = _tmp7_;
	_tmp9_ = level;
	_tmp10_ = self->domain;
	_tmp11_ = repr;
	_tmp12_ = message;
	_tmp13_ = g_strdup_printf ("%s %s %s %s: %s\n", _tmp8_, _tmp9_, _tmp10_, _tmp11_, _tmp12_);
	_tmp14_ = _tmp13_;
	_g_free0 (_tmp8_);
	str = _tmp14_;
	_tmp16_ = self->colored;
	if (_tmp16_) {
		const gchar* _tmp17_ = NULL;
		const gchar* _tmp18_ = NULL;
		gchar* _tmp19_ = NULL;
		_tmp17_ = str;
		_tmp18_ = level;
		_tmp19_ = fso_framework_abstract_logger_colorwrap (self, _tmp17_, _tmp18_);
		_g_free0 (_tmp15_);
		_tmp15_ = _tmp19_;
	} else {
		const gchar* _tmp20_ = NULL;
		gchar* _tmp21_ = NULL;
		_tmp20_ = str;
		_tmp21_ = g_strdup (_tmp20_);
		_g_free0 (_tmp15_);
		_tmp15_ = _tmp21_;
	}
	result = _tmp15_;
	_g_free0 (str);
	_g_free0 (repr);
	_g_free0 (_tmp0_);
	return result;
}
