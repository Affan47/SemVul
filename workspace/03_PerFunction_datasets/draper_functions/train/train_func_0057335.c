fso_gsm_plus_ccfc_issue_ext (FsoGsmPlusCCFC* self, FsoGsmConstantsCallForwardingMode mode, FsoGsmConstantsCallForwardingType type, FsoGsmConstantsBearerClass cls, const gchar* number, gint time) {
	gchar* result = NULL;
	gint number_type = 0;
	const gchar* _tmp0_ = NULL;
	guint8 _tmp1_ = 0U;
	gchar* command = NULL;
	FsoGsmConstantsCallForwardingType _tmp2_ = 0;
	FsoGsmConstantsCallForwardingMode _tmp3_ = 0;
	const gchar* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	FsoGsmConstantsBearerClass _tmp6_ = 0;
	gchar* _tmp7_ = NULL;
	gboolean _tmp8_ = FALSE;
	gboolean _tmp9_ = FALSE;
	FsoGsmConstantsCallForwardingType _tmp10_ = 0;
	gboolean _tmp12_ = FALSE;
	gboolean _tmp14_ = FALSE;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (number != NULL, NULL);
	_tmp0_ = number;
	_tmp1_ = fso_gsm_constants_determinePhoneNumberType (_tmp0_);
	number_type = (gint) _tmp1_;
	_tmp2_ = type;
	_tmp3_ = mode;
	_tmp4_ = number;
	_tmp5_ = number_type;
	_tmp6_ = cls;
	_tmp7_ = g_strdup_printf ("+CCFC=%d,%d,\"%s\",%d,%d", (gint) _tmp2_, (gint) _tmp3_, _tmp4_, _tmp5_, (gint) _tmp6_);
	command = _tmp7_;
	_tmp10_ = type;
	if (_tmp10_ == FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_NO_REPLY) {
		_tmp9_ = TRUE;
	} else {
		FsoGsmConstantsCallForwardingType _tmp11_ = 0;
		_tmp11_ = type;
		_tmp9_ = _tmp11_ == FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_ALL;
	}
	_tmp12_ = _tmp9_;
	if (_tmp12_) {
		_tmp8_ = TRUE;
	} else {
		FsoGsmConstantsCallForwardingType _tmp13_ = 0;
		_tmp13_ = type;
		_tmp8_ = _tmp13_ == FSO_GSM_CONSTANTS_CALL_FORWARDING_TYPE_ALL_CONDITIONAL;
	}
	_tmp14_ = _tmp8_;
	if (_tmp14_) {
		const gchar* _tmp15_ = NULL;
		gint _tmp16_ = 0;
		gchar* _tmp17_ = NULL;
		gchar* _tmp18_ = NULL;
		gchar* _tmp19_ = NULL;
		_tmp15_ = command;
		_tmp16_ = time;
		_tmp17_ = g_strdup_printf (",,,%d", _tmp16_);
		_tmp18_ = _tmp17_;
		_tmp19_ = g_strconcat (_tmp15_, _tmp18_, NULL);
		_g_free0 (command);
		command = _tmp19_;
		_g_free0 (_tmp18_);
	}
	result = command;
	return result;
}
