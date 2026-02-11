gee_priority_queue_real_drain (GeeAbstractQueue* base, GeeCollection* recipient, gint amount) {
	GeePriorityQueue * self;
	gint result = 0;
	gint _tmp0_ = 0;
	gint _tmp11_ = 0;
	self = (GeePriorityQueue*) base;
	g_return_val_if_fail (recipient != NULL, 0);
	_tmp0_ = amount;
	if (_tmp0_ == (-1)) {
		gint _tmp1_ = 0;
		_tmp1_ = self->priv->_size;
		amount = _tmp1_;
	}
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp2_ = FALSE;
			_tmp2_ = TRUE;
			while (TRUE) {
				gboolean _tmp3_ = FALSE;
				gint _tmp5_ = 0;
				gint _tmp6_ = 0;
				gint _tmp7_ = 0;
				GeeCollection* _tmp8_ = NULL;
				gpointer _tmp9_ = NULL;
				gpointer _tmp10_ = NULL;
				_tmp3_ = _tmp2_;
				if (!_tmp3_) {
					gint _tmp4_ = 0;
					_tmp4_ = i;
					i = _tmp4_ + 1;
				}
				_tmp2_ = FALSE;
				_tmp5_ = i;
				_tmp6_ = amount;
				if (!(_tmp5_ < _tmp6_)) {
					break;
				}
				_tmp7_ = self->priv->_size;
				if (_tmp7_ == 0) {
					result = i;
					return result;
				}
				_tmp8_ = recipient;
				_tmp9_ = gee_abstract_queue_poll ((GeeAbstractQueue*) self);
				_tmp10_ = _tmp9_;
				gee_collection_add (_tmp8_, _tmp10_);
				((_tmp10_ == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (_tmp10_ = (self->priv->g_destroy_func (_tmp10_), NULL));
			}
		}
	}
	_tmp11_ = amount;
	result = _tmp11_;
	return result;
}
