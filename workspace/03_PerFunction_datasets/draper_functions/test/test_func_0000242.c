fso_gsm_service_checkAvailability (FsoGsmService* self, FsoGsmModemStatus required, GError** error) {
	FsoGsmModem* _tmp0_ = NULL;
	gboolean _tmp2_ = FALSE;
	FsoGsmModem* _tmp3_ = NULL;
	FsoGsmModemStatus _tmp4_ = 0;
	FsoGsmModemStatus _tmp5_ = 0;
	gboolean _tmp8_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->modem;
	if (_tmp0_ == NULL) {
		GError* _tmp1_ = NULL;
		_tmp1_ = g_error_new_literal (FREE_SMARTPHONE_ERROR, FREE_SMARTPHONE_ERROR_UNAVAILABLE, "There is no underlying hardware present... stop talking to a vapourwar" \
"e modem!");
		_inner_error_ = _tmp1_;
		if (_inner_error_->domain == FREE_SMARTPHONE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp3_ = self->modem;
	_tmp4_ = fso_gsm_modem_status (_tmp3_);
	_tmp5_ = required;
	if (_tmp4_ < _tmp5_) {
		_tmp2_ = TRUE;
	} else {
		FsoGsmModem* _tmp6_ = NULL;
		FsoGsmModemStatus _tmp7_ = 0;
		_tmp6_ = self->modem;
		_tmp7_ = fso_gsm_modem_status (_tmp6_);
		_tmp2_ = _tmp7_ >= FSO_GSM_MODEM_STATUS_SUSPENDING;
	}
	_tmp8_ = _tmp2_;
	if (_tmp8_) {
		FsoGsmModem* _tmp9_ = NULL;
		FsoGsmModemStatus _tmp10_ = 0;
		GEnumValue* _tmp11_;
		gchar* _tmp12_ = NULL;
		gchar* _tmp13_ = NULL;
		GError* _tmp14_ = NULL;
		GError* _tmp15_ = NULL;
		_tmp9_ = self->modem;
		_tmp10_ = fso_gsm_modem_status (_tmp9_);
		_tmp11_ = g_enum_get_value (g_type_class_ref (FSO_GSM_MODEM_TYPE_STATUS), _tmp10_);
		_tmp12_ = g_strconcat ("This function is not available while modem is in state ", (_tmp11_ != NULL) ? _tmp11_->value_name : NULL, NULL);
		_tmp13_ = _tmp12_;
		_tmp14_ = g_error_new_literal (FREE_SMARTPHONE_ERROR, FREE_SMARTPHONE_ERROR_UNAVAILABLE, _tmp13_);
		_tmp15_ = _tmp14_;
		_g_free0 (_tmp13_);
		_inner_error_ = _tmp15_;
		if (_inner_error_->domain == FREE_SMARTPHONE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
