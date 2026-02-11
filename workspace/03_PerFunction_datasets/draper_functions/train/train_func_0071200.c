gee_array_list_iterator_real_get_valid (GeeIterator* base) {
	gboolean result;
	GeeArrayListIterator* self;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gint _tmp2_ = 0;
	gboolean _tmp6_ = FALSE;
	gboolean _tmp8_ = FALSE;
	self = (GeeArrayListIterator*) base;
	_tmp2_ = self->priv->_index;
	if (_tmp2_ >= 0) {
		gint _tmp3_ = 0;
		GeeArrayList* _tmp4_ = NULL;
		gint _tmp5_ = 0;
		_tmp3_ = self->priv->_index;
		_tmp4_ = self->priv->_list;
		_tmp5_ = _tmp4_->_size;
		_tmp1_ = _tmp3_ < _tmp5_;
	} else {
		_tmp1_ = FALSE;
	}
	_tmp6_ = _tmp1_;
	if (_tmp6_) {
		gboolean _tmp7_ = FALSE;
		_tmp7_ = self->priv->_removed;
		_tmp0_ = !_tmp7_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp8_ = _tmp0_;
	result = _tmp8_;
	return result;
}
