gee_tree_set_sub_iterator_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeTreeSet* set, GeeTreeSetRange* range) {
	GeeTreeSetSubIterator * self = NULL;
	GeeTreeSet* _tmp0_ = NULL;
	GeeTreeSet* _tmp1_ = NULL;
	GeeTreeSetRange* _tmp2_ = NULL;
	GeeTreeSetRange* _tmp3_ = NULL;
	g_return_val_if_fail (set != NULL, NULL);
	g_return_val_if_fail (range != NULL, NULL);
	self = (GeeTreeSetSubIterator*) g_object_new (object_type, NULL);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = set;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->set);
	self->priv->set = _tmp1_;
	_tmp2_ = range;
	_tmp3_ = _gee_tree_set_range_ref0 (_tmp2_);
	_gee_tree_set_range_unref0 (self->priv->range);
	self->priv->range = _tmp3_;
	return self;
}
