gee_array_queue_iterator_real_get_valid (GeeIterator* base) {
	gboolean result;
	GeeArrayQueueIterator* self;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	gboolean _tmp3_ = FALSE;
	self = (GeeArrayQueueIterator*) base;
	_tmp1_ = self->priv->_offset;
	if (_tmp1_ != (-1)) {
		gboolean _tmp2_ = FALSE;
		_tmp2_ = self->priv->_removed;
		_tmp0_ = !_tmp2_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp3_ = _tmp0_;
	result = _tmp3_;
	return result;
}
