kernel26_power_supply_isPresent (Kernel26PowerSupply* self) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gchar* node = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar* value = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	gchar* _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
	gboolean _tmp10_ = FALSE;
	const gchar* _tmp11_ = NULL;
	gboolean _tmp13_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp1_ = kernel26_power_supply_isBattery (self);
	if (_tmp1_) {
		_tmp0_ = "%s/present";
	} else {
		_tmp0_ = "%s/online";
	}
	_tmp2_ = _tmp0_;
	_tmp3_ = g_strdup (_tmp2_);
	node = _tmp3_;
	_tmp4_ = node;
	_tmp5_ = self->priv->sysfsnode;
	_tmp6_ = g_strdup_printf (_tmp4_, _tmp5_);
	_tmp7_ = _tmp6_;
	_tmp8_ = fso_framework_file_handling_read (_tmp7_);
	_tmp9_ = _tmp8_;
	_g_free0 (_tmp7_);
	value = _tmp9_;
	_tmp11_ = value;
	if (_tmp11_ != NULL) {
		const gchar* _tmp12_ = NULL;
		_tmp12_ = value;
		_tmp10_ = g_strcmp0 (_tmp12_, "1") == 0;
	} else {
		_tmp10_ = FALSE;
	}
	_tmp13_ = _tmp10_;
	result = _tmp13_;
	_g_free0 (value);
	_g_free0 (node);
	return result;
}
