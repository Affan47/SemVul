fso_gsm_at_unsolicited_response_handler_real_plusCRING (FsoGsmAtUnsolicitedResponseHandler* self, const gchar* prefix, const gchar* rhs) {
	FsoGsmModem* _tmp0_ = NULL;
	FsoGsmModem* _tmp1_ = NULL;
	FsoGsmCallHandler* _tmp2_ = NULL;
	FsoGsmCallHandler* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	FsoGsmCallInfo* _tmp5_ = NULL;
	FsoGsmCallInfo* _tmp6_ = NULL;
	g_return_if_fail (prefix != NULL);
	g_return_if_fail (rhs != NULL);
	_tmp0_ = fso_gsm_base_unsolicited_response_handler_get_modem ((FsoGsmBaseUnsolicitedResponseHandler*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = fso_gsm_modem_get_callhandler (_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = rhs;
	_tmp5_ = fso_gsm_call_info_new_with_ctype (_tmp4_);
	_tmp6_ = _tmp5_;
	fso_gsm_call_handler_handleIncomingCall (_tmp3_, _tmp6_);
	_g_object_unref0 (_tmp6_);
}
