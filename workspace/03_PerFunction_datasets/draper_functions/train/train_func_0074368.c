cinterion_mc75_modem_real_channelForCommand (FsoGsmAbstractModem* base, FsoGsmAtCommand* command, const gchar* query) {
	CinterionMc75Modem * self;
	FsoGsmChannel* result = NULL;
	gboolean _tmp0_ = FALSE;
	const gchar* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp5_ = FALSE;
	GeeHashMap* _tmp8_ = NULL;
	gpointer _tmp9_ = NULL;
	self = (CinterionMc75Modem*) base;
	g_return_val_if_fail (command != NULL, NULL);
	g_return_val_if_fail (query != NULL, NULL);
	_tmp1_ = query;
	_tmp2_ = g_str_has_prefix (_tmp1_, "D*99");
	if (_tmp2_) {
		_tmp0_ = TRUE;
	} else {
		const gchar* _tmp3_ = NULL;
		gboolean _tmp4_ = FALSE;
		_tmp3_ = query;
		_tmp4_ = g_str_has_prefix (_tmp3_, "+CGD");
		_tmp0_ = _tmp4_;
	}
	_tmp5_ = _tmp0_;
	if (_tmp5_) {
		GeeHashMap* _tmp6_ = NULL;
		gpointer _tmp7_ = NULL;
		_tmp6_ = ((FsoGsmAbstractModem*) self)->channels;
		_tmp7_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp6_, "data");
		result = (FsoGsmChannel*) _tmp7_;
		return result;
	}
	_tmp8_ = ((FsoGsmAbstractModem*) self)->channels;
	_tmp9_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp8_, "main");
	result = (FsoGsmChannel*) _tmp9_;
	return result;
}
