unity_protocol_scope_proxy_new_for_id (const gchar* id, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	UnityProtocolScopeProxyNewForIdData* _data_;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	GCancellable* _tmp2_ = NULL;
	GCancellable* _tmp3_ = NULL;
	_data_ = g_slice_new0 (UnityProtocolScopeProxyNewForIdData);
	_data_->_dummy_object_ = g_object_newv (G_TYPE_OBJECT, 0, NULL);
	_data_->_async_result = g_simple_async_result_new (_data_->_dummy_object_, _callback_, _user_data_, unity_protocol_scope_proxy_new_for_id);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, unity_protocol_scope_proxy_new_for_id_data_free);
	_tmp0_ = id;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (_data_->id);
	_data_->id = _tmp1_;
	_tmp2_ = cancellable;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_g_object_unref0 (_data_->cancellable);
	_data_->cancellable = _tmp3_;
	unity_protocol_scope_proxy_new_for_id_co (_data_);
}
