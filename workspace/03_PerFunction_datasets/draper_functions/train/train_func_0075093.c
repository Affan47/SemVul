fso_gsm_pdp_handler_real_disconnected (FsoGsmIPdpHandler* base) {
	FsoGsmPdpHandler * self;
	GHashTable* status = NULL;
	GHashFunc _tmp0_ = NULL;
	GEqualFunc _tmp1_ = NULL;
	GHashTable* _tmp2_ = NULL;
	self = (FsoGsmPdpHandler*) base;
	_tmp0_ = g_str_hash;
	_tmp1_ = g_str_equal;
	_tmp2_ = g_hash_table_new_full (_tmp0_, _tmp1_, _g_free0_, _g_variant_unref0_);
	status = _tmp2_;
	fso_gsm_pdp_handler_updateStatus (self, FREE_SMARTPHONE_GSM_CONTEXT_STATUS_RELEASED, status, NULL, NULL);
	_g_hash_table_unref0 (status);
}
