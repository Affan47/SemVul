kernel26_aggregate_power_supply_sendStatusIfChanged (Kernel26AggregatePowerSupply* self, FreeSmartphoneDevicePowerStatus status) {
	FsoFrameworkLogger* _tmp0_ = NULL;
	FreeSmartphoneDevicePowerStatus _tmp1_ = 0;
	FreeSmartphoneDevicePowerStatus _tmp2_ = 0;
	gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	gboolean _tmp5_ = FALSE;
	FreeSmartphoneDevicePowerStatus _tmp6_ = 0;
	gboolean _tmp8_ = FALSE;
	FreeSmartphoneDevicePowerStatus _tmp10_ = 0;
	FreeSmartphoneDevicePowerStatus _tmp11_ = 0;
	FreeSmartphoneDevicePowerStatus _tmp12_ = 0;
	FreeSmartphoneDevicePowerStatus _tmp13_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((FsoFrameworkAbstractObject*) self)->logger;
	_tmp1_ = self->priv->status;
	_tmp2_ = status;
	_tmp3_ = g_strdup_printf ("sendStatusIfChanged old %d new %d", (gint) _tmp1_, (gint) _tmp2_);
	_tmp4_ = _tmp3_;
	fso_framework_logger_debug (_tmp0_, _tmp4_);
	_g_free0 (_tmp4_);
	_tmp6_ = self->priv->status;
	if (_tmp6_ == FREE_SMARTPHONE_DEVICE_POWER_STATUS_DISCHARGING) {
		FreeSmartphoneDevicePowerStatus _tmp7_ = 0;
		_tmp7_ = status;
		_tmp5_ = _tmp7_ == FREE_SMARTPHONE_DEVICE_POWER_STATUS_FULL;
	} else {
		_tmp5_ = FALSE;
	}
	_tmp8_ = _tmp5_;
	if (_tmp8_) {
		FsoFrameworkLogger* _tmp9_ = NULL;
		_tmp9_ = ((FsoFrameworkAbstractObject*) self)->logger;
		fso_framework_logger_warning (_tmp9_, "BUG: power supply class sent 'full' after 'discharging'");
		return;
	}
	_tmp10_ = self->priv->status;
	_tmp11_ = status;
	if (_tmp10_ == _tmp11_) {
		return;
	}
	_tmp12_ = status;
	self->priv->status = _tmp12_;
	_tmp13_ = status;
	g_signal_emit_by_name ((FreeSmartphoneDevicePowerSupply*) self, "power-status", _tmp13_);
}
