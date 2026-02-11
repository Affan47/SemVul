low_level_gt_a04_real_poweron (FsoGsmLowLevel* base) {
	LowLevelGTA04 * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	FsoFrameworkLogger* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	gboolean _tmp5_ = FALSE;
	self = (LowLevelGTA04*) base;
	_tmp0_ = fso_gsm_low_level_poweroff ((FsoGsmLowLevel*) self);
	if (!_tmp0_) {
		FsoFrameworkLogger* _tmp1_ = NULL;
		gboolean _tmp2_ = FALSE;
		_tmp1_ = ((FsoFrameworkAbstractObject*) self)->logger;
		_tmp2_ = fso_framework_logger_debug (_tmp1_, "Already active modem could not powered off!");
		_vala_assert (_tmp2_, "logger.debug( @\"Already active modem could not powered off!\" )");
		result = FALSE;
		return result;
	}
	_tmp3_ = ((FsoFrameworkAbstractObject*) self)->logger;
	_tmp4_ = fso_framework_logger_debug (_tmp3_, "Powering modem on now ...");
	_vala_assert (_tmp4_, "logger.debug( @\"Powering modem on now ...\" )");
	_tmp5_ = low_level_gt_a04_toggle_modem_power_state (self, TRUE);
	result = _tmp5_;
	return result;
}
