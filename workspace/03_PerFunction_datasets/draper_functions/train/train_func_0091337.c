gee_abstract_multi_set_iterator_real_has_next (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	gboolean _tmp4_ = FALSE;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp1_ = self->priv->_pending;
	if (_tmp1_ > 0) {
		_tmp0_ = TRUE;
	} else {
		GeeMapIterator* _tmp2_ = NULL;
		gboolean _tmp3_ = FALSE;
		_tmp2_ = self->priv->_iter;
		_tmp3_ = gee_map_iterator_has_next (_tmp2_);
		_tmp0_ = _tmp3_;
	}
	_tmp4_ = _tmp0_;
	result = _tmp4_;
	return result;
}
