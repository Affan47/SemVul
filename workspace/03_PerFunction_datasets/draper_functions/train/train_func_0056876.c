edsf_memory_icon_real_load_async (GLoadableIcon* base, gint size, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	EdsfMemoryIcon * self;
	EdsfMemoryIconLoadAsyncData* _data_;
	EdsfMemoryIcon* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	GCancellable* _tmp2_ = NULL;
	GCancellable* _tmp3_ = NULL;
	self = (EdsfMemoryIcon*) base;
	_data_ = g_slice_new0 (EdsfMemoryIconLoadAsyncData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, edsf_memory_icon_real_load_async);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, edsf_memory_icon_real_load_async_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	_tmp1_ = size;
	_data_->size = _tmp1_;
	_tmp2_ = cancellable;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_g_object_unref0 (_data_->cancellable);
	_data_->cancellable = _tmp3_;
	edsf_memory_icon_real_load_async_co (_data_);
}
