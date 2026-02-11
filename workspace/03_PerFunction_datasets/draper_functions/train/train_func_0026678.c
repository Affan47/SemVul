gee_linked_list_iterator_real_index (GeeListIterator* base) {
	GeeLinkedListIterator * self;
	gint result = 0;
	gint _tmp0_ = 0;
	GeeLinkedList* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	GeeLinkedListNode* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	self = (GeeLinkedListIterator*) base;
	_tmp0_ = self->priv->_stamp;
	_tmp1_ = self->priv->_list;
	_tmp2_ = _tmp1_->priv->_stamp;
	_vala_assert (_tmp0_ == _tmp2_, "this._stamp == this._list._stamp");
	_tmp3_ = self->priv->position;
	_vala_assert (_tmp3_ != NULL, "this.position != null");
	_tmp4_ = self->priv->_index;
	result = _tmp4_;
	return result;
}
