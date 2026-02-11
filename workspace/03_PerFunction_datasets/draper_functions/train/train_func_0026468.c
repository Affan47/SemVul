gee_array_list_iterator_real_has_next (GeeIterator* base) {
	GeeArrayListIterator * self;
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	GeeArrayList* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	GeeArrayList* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	self = (GeeArrayListIterator*) base;
	_tmp0_ = self->priv->_stamp;
	_tmp1_ = self->priv->_list;
	_tmp2_ = _tmp1_->priv->_stamp;
	_vala_assert (_tmp0_ == _tmp2_, "_stamp == _list._stamp");
	_tmp3_ = self->priv->_index;
	_tmp4_ = self->priv->_list;
	_tmp5_ = _tmp4_->_size;
	result = (_tmp3_ + 1) < _tmp5_;
	return result;
}
