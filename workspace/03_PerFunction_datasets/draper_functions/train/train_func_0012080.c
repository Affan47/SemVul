_gee_priority_queue_iterator_get_next_node (GeePriorityQueueIterator* self) {
	GeePriorityQueueNode* result = NULL;
	GeePriorityQueueNode* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->position;
	if (_tmp0_ != NULL) {
		GeePriorityQueueNode* _tmp1_ = NULL;
		GeePriorityQueueNode* _tmp2_ = NULL;
		_tmp1_ = self->priv->position;
		_tmp2_ = _tmp1_->iter_next;
		result = _tmp2_;
		return result;
	} else {
		GeePriorityQueueNode* _tmp3_ = NULL;
		GeePriorityQueueNode* _tmp4_ = NULL;
		GeePriorityQueueNode* _tmp9_ = NULL;
		_tmp4_ = self->priv->previous;
		if (_tmp4_ != NULL) {
			GeePriorityQueueNode* _tmp5_ = NULL;
			GeePriorityQueueNode* _tmp6_ = NULL;
			_tmp5_ = self->priv->previous;
			_tmp6_ = _tmp5_->iter_next;
			_tmp3_ = _tmp6_;
		} else {
			GeePriorityQueue* _tmp7_ = NULL;
			GeePriorityQueueNode* _tmp8_ = NULL;
			_tmp7_ = self->priv->queue;
			_tmp8_ = _tmp7_->priv->_iter_head;
			_tmp3_ = _tmp8_;
		}
		_tmp9_ = _tmp3_;
		result = _tmp9_;
		return result;
	}
}
