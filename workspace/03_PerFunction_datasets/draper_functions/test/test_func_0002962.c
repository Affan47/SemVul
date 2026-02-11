tds_model_read_uint16 (TDSModel* self, GInputStream* stream, GError** error) {
	guint16 result = 0U;
	guchar buffer[2] = {0};
	GInputStream* _tmp0_;
	guchar _tmp1_;
	guchar _tmp2_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, 0U);
	g_return_val_if_fail (stream != NULL, 0U);
	_tmp0_ = stream;
	g_input_stream_read_all (_tmp0_, (void*) buffer, (gsize) 2, NULL, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return 0U;
	}
	_tmp1_ = buffer[1];
	_tmp2_ = buffer[0];
	result = (guint16) ((_tmp1_ << 8) | _tmp2_);
	return result;
}
