gee_abstract_multi_set_iterator_real_get_valid (GeeIterator* base) {
	gboolean result;
	GeeAbstractMultiSetIterator* self;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp5_ = FALSE;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp1_ = self->priv->_removed;
	if (!_tmp1_) {
		GeeMapIterator* _tmp2_ = NULL;
		gboolean _tmp3_ = FALSE;
		gboolean _tmp4_ = FALSE;
		_tmp2_ = self->priv->_iter;
		_tmp3_ = gee_map_iterator_get_valid (_tmp2_);
		_tmp4_ = _tmp3_;
		_tmp0_ = _tmp4_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	result = _tmp5_;
	return result;
}
