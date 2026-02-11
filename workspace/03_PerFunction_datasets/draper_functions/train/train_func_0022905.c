gee_priority_queue_real_remove (GeeAbstractCollection* base, gconstpointer item) {
	GeePriorityQueue * self;
	gboolean result = FALSE;
	GeePriorityQueueIterator* iterator = NULL;
	GeePriorityQueueIterator* _tmp0_ = NULL;
	self = (GeePriorityQueue*) base;
	_tmp0_ = gee_priority_queue_iterator_new (self->priv->g_type, (GBoxedCopyFunc) self->priv->g_dup_func, self->priv->g_destroy_func, self);
	iterator = _tmp0_;
	while (TRUE) {
		GeePriorityQueueIterator* _tmp1_ = NULL;
		gboolean _tmp2_ = FALSE;
		gpointer an_item = NULL;
		GeePriorityQueueIterator* _tmp3_ = NULL;
		gpointer _tmp4_ = NULL;
		GCompareDataFunc _tmp5_ = NULL;
		void* _tmp5__target = NULL;
		GCompareDataFunc _tmp6_ = NULL;
		void* _tmp6__target = NULL;
		gconstpointer _tmp7_ = NULL;
		gconstpointer _tmp8_ = NULL;
		gint _tmp9_ = 0;
		_tmp1_ = iterator;
		_tmp2_ = gee_iterator_next ((GeeIterator*) _tmp1_);
		if (!_tmp2_) {
			break;
		}
		_tmp3_ = iterator;
		_tmp4_ = gee_iterator_get ((GeeIterator*) _tmp3_);
		an_item = _tmp4_;
		_tmp5_ = gee_priority_queue_get_compare_func (self, &_tmp5__target);
		_tmp6_ = _tmp5_;
		_tmp6__target = _tmp5__target;
		_tmp7_ = item;
		_tmp8_ = an_item;
		_tmp9_ = _tmp6_ (_tmp7_, _tmp8_, _tmp6__target);
		if (_tmp9_ == 0) {
			GeePriorityQueueIterator* _tmp10_ = NULL;
			_tmp10_ = iterator;
			gee_iterator_remove ((GeeIterator*) _tmp10_);
			result = TRUE;
			((an_item == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (an_item = (self->priv->g_destroy_func (an_item), NULL));
			_g_object_unref0 (iterator);
			return result;
		}
		((an_item == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (an_item = (self->priv->g_destroy_func (an_item), NULL));
	}
	result = FALSE;
	_g_object_unref0 (iterator);
	return result;
}
