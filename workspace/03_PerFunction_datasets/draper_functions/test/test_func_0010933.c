async_process_launch (AsyncProcess* self, GCancellable* cancel, gchar** argv, int argv_length1, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	AsyncProcessLaunchData* _data_;
	AsyncProcess* _tmp0_ = NULL;
	GCancellable* _tmp1_ = NULL;
	GCancellable* _tmp2_ = NULL;
	gchar** _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	_data_ = g_slice_new0 (AsyncProcessLaunchData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, async_process_launch);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, async_process_launch_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	_tmp1_ = cancel;
	_tmp2_ = _g_object_ref0 (_tmp1_);
	_g_object_unref0 (_data_->cancel);
	_data_->cancel = _tmp2_;
	_tmp3_ = argv;
	_tmp3__length1 = argv_length1;
	_data_->argv = _tmp3_;
	_data_->argv_length1 = _tmp3__length1;
	async_process_launch_co (_data_);
}
