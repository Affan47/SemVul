boxes_exec_finish (GAsyncResult* _res_, gchar** standard_output, gchar** standard_error, GError** error) {
	BoxesExecData* _data_;
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
		return;
	}
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
	if (standard_output) {
		*standard_output = _data_->standard_output;
	} else {
		_g_free0 (_data_->standard_output);
	}
	_data_->standard_output = NULL;
	if (standard_error) {
		*standard_error = _data_->standard_error;
	} else {
		_g_free0 (_data_->standard_error);
	}
	_data_->standard_error = NULL;
}
