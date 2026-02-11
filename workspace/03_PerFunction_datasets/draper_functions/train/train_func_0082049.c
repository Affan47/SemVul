fso_gsm_gsm_call_forwarding_service_reason_from_rule_name (FsoGsmGsmCallForwardingService* self, const gchar* name, GError** error) {
	FsoGsmConstantsCallForwardingType result = 0;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GQuark _tmp3_ = 0U;
	static GQuark _tmp2_label0 = 0;
	static GQuark _tmp2_label1 = 0;
	static GQuark _tmp2_label2 = 0;
	static GQuark _tmp2_label3 = 0;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	GError* _tmp8_ = NULL;
	GError* _tmp9_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (name != NULL, 0);
	_tmp0_ = name;
	_tmp1_ = _tmp0_;
	_tmp3_ = (NULL == _tmp1_) ? 0 : g_quark_from_string (_tmp1_);
	if (_tmp3_ == ((0 != _tmp2_label0) ? _tmp2_label0 : (_tmp2_label0 = g_quark_from_static_string ("voice unconditional")))) {
		switch (0) {
			default:
			{
				result = FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_UNCONDITIONAL;
				return result;
			}
		}
	} else if (_tmp3_ == ((0 != _tmp2_label1) ? _tmp2_label1 : (_tmp2_label1 = g_quark_from_static_string ("voice busy")))) {
		switch (0) {
			default:
			{
				result = FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_BUSY;
				return result;
			}
		}
	} else if (_tmp3_ == ((0 != _tmp2_label2) ? _tmp2_label2 : (_tmp2_label2 = g_quark_from_static_string ("voice no reply")))) {
		switch (0) {
			default:
			{
				result = FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_NO_REPLY;
				return result;
			}
		}
	} else if (_tmp3_ == ((0 != _tmp2_label3) ? _tmp2_label3 : (_tmp2_label3 = g_quark_from_static_string ("voice not reachable")))) {
		switch (0) {
			default:
			{
				result = FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_NOT_REACHABLE;
				return result;
			}
		}
	}
	_tmp4_ = name;
	_tmp5_ = string_to_string (_tmp4_);
	_tmp6_ = g_strconcat ("Invalid rule name: ", _tmp5_, NULL);
	_tmp7_ = _tmp6_;
	_tmp8_ = g_error_new_literal (FREE_SMARTPHONE_ERROR, FREE_SMARTPHONE_ERROR_INVALID_PARAMETER, _tmp7_);
	_tmp9_ = _tmp8_;
	_g_free0 (_tmp7_);
	_inner_error_ = _tmp9_;
	if (_inner_error_->domain == FREE_SMARTPHONE_ERROR) {
		g_propagate_error (error, _inner_error_);
		return 0;
	} else {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
}
