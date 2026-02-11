unity_internal_io_read_stream_finish (GAsyncResult* _res_, guint8** data, int* data_length1, gsize* size, GError** error) {
	UnityInternalIoReadStreamAsyncData* _data_;
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
		return;
	}
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
	if (data) {
		*data = _data_->data;
	} else {
		_data_->data = (g_free (_data_->data), NULL);
	}
	if (data_length1) {
		*data_length1 = _data_->data_length1;
	}
	_data_->data = NULL;
	if (size) {
		*size = _data_->size;
	}
}
