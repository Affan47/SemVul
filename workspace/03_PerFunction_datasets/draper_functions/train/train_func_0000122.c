gee_concurrent_set_sub_iterator_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeConcurrentSetRange* range) {
	GeeConcurrentSetSubIterator * self = NULL;
	GeeConcurrentSetRange* _tmp0_ = NULL;
	GeeConcurrentSetRange* _tmp1_ = NULL;
	GeeConcurrentSetRange* _tmp2_ = NULL;
	g_return_val_if_fail (range != NULL, NULL);
	self = (GeeConcurrentSetSubIterator*) g_object_new (object_type, NULL);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = range;
	gee_concurrent_set_range_improve_bookmark (g_type, (GBoxedCopyFunc) g_dup_func, g_destroy_func, _tmp0_, NULL, NULL);
	_tmp1_ = range;
	_tmp2_ = _gee_concurrent_set_range_ref0 (_tmp1_);
	_gee_concurrent_set_range_unref0 (self->priv->_range);
	self->priv->_range = _tmp2_;
	return self;
}
