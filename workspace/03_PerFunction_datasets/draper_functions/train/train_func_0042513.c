fso_gsm_plus_cmgr_real_parseMulti (FsoGsmAbstractAtCommand* base, gchar** response, int response_length1, GError** error) {
	FsoGsmPlusCMGR * self;
	gchar** _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	const gchar* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gchar** _tmp4_ = NULL;
	gint _tmp4__length1 = 0;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	GError * _inner_error_ = NULL;
	self = (FsoGsmPlusCMGR*) base;
	_tmp0_ = response;
	_tmp0__length1 = response_length1;
	_tmp1_ = _tmp0_[0];
	FSO_GSM_ABSTRACT_AT_COMMAND_CLASS (fso_gsm_plus_cmgr_parent_class)->parse (G_TYPE_CHECK_INSTANCE_CAST (self, FSO_GSM_TYPE_ABSTRACT_AT_COMMAND, FsoGsmAbstractAtCommand), _tmp1_, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == FSO_GSM_AT_COMMAND_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp2_ = fso_gsm_abstract_at_command_to_int ((FsoGsmAbstractAtCommand*) self, "stat");
	self->status = (FsoGsmPlusCMGLMode) _tmp2_;
	_tmp3_ = fso_gsm_abstract_at_command_to_int ((FsoGsmAbstractAtCommand*) self, "tpdulen");
	self->tpdulen = _tmp3_;
	_tmp4_ = response;
	_tmp4__length1 = response_length1;
	_tmp5_ = _tmp4_[1];
	_tmp6_ = g_strdup (_tmp5_);
	_g_free0 (self->hexpdu);
	self->hexpdu = _tmp6_;
}
