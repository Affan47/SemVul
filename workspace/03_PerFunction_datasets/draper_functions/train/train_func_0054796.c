fso_gsm_at_unsolicited_response_handler_construct (GType object_type, FsoGsmModem* modem) {
	FsoGsmAtUnsolicitedResponseHandler * self = NULL;
	FsoGsmModem* _tmp0_ = NULL;
	g_return_val_if_fail (modem != NULL, NULL);
	_tmp0_ = modem;
	self = (FsoGsmAtUnsolicitedResponseHandler*) fso_gsm_base_unsolicited_response_handler_construct (object_type, _tmp0_);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CALA", _fso_gsm_at_unsolicited_response_handler_plusCALA_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CCWA", _fso_gsm_at_unsolicited_response_handler_plusCCWA_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CGEV", _fso_gsm_at_unsolicited_response_handler_plusCGEV_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CGREG", _fso_gsm_at_unsolicited_response_handler_plusCGREG_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CIEV", _fso_gsm_at_unsolicited_response_handler_plusCIEV_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CLIP", _fso_gsm_at_unsolicited_response_handler_plusCLIP_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CMTI", _fso_gsm_at_unsolicited_response_handler_plusCMTI_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CREG", _fso_gsm_at_unsolicited_response_handler_plusCREG_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CRING", _fso_gsm_at_unsolicited_response_handler_plusCRING_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CSSI", _fso_gsm_at_unsolicited_response_handler_plusCSSI_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CSSU", _fso_gsm_at_unsolicited_response_handler_plusCSSU_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CTZV", _fso_gsm_at_unsolicited_response_handler_plusCTZV_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CUSD", _fso_gsm_at_unsolicited_response_handler_plusCUSD_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrc ((FsoGsmBaseUnsolicitedResponseHandler*) self, "NO CARRIER", _fso_gsm_at_unsolicited_response_handler_no_carrier_unsolicited_response_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrcPdu ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CBM", _fso_gsm_at_unsolicited_response_handler_plusCBM_unsolicited_response_pdu_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrcPdu ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CDS", _fso_gsm_at_unsolicited_response_handler_plusCDS_unsolicited_response_pdu_handler_func, self);
	fso_gsm_base_unsolicited_response_handler_registerUrcPdu ((FsoGsmBaseUnsolicitedResponseHandler*) self, "+CMT", _fso_gsm_at_unsolicited_response_handler_plusCMT_unsolicited_response_pdu_handler_func, self);
	return self;
}
