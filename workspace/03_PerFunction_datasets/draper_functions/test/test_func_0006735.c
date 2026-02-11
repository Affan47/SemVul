fso_gsm_gsm_pdp_service_real_internal_status_update (FreeSmartphoneGSMPDP* base, const gchar* status, GHashTable* properties, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	FsoGsmGsmPdpService * self;
	FsoGsmGsmPdpServiceInternalStatusUpdateData* _data_;
	FsoGsmGsmPdpService* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	GHashTable* _tmp3_ = NULL;
	GHashTable* _tmp4_ = NULL;
	self = (FsoGsmGsmPdpService*) base;
	_data_ = g_slice_new0 (FsoGsmGsmPdpServiceInternalStatusUpdateData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, fso_gsm_gsm_pdp_service_real_internal_status_update);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, fso_gsm_gsm_pdp_service_real_internal_status_update_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	_tmp1_ = status;
	_tmp2_ = g_strdup (_tmp1_);
	_g_free0 (_data_->status);
	_data_->status = _tmp2_;
	_tmp3_ = properties;
	_tmp4_ = _g_hash_table_ref0 (_tmp3_);
	_g_hash_table_unref0 (_data_->properties);
	_data_->properties = _tmp4_;
	fso_gsm_gsm_pdp_service_real_internal_status_update_co (_data_);
}
