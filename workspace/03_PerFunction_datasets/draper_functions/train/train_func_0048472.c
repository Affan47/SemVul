gee_tree_map_real_head_map (GeeAbstractSortedMap* base, gconstpointer before) {
	GeeTreeMap * self;
	GeeSortedMap* result = NULL;
	gconstpointer _tmp0_ = NULL;
	GeeTreeMapRange* _tmp1_ = NULL;
	GeeTreeMapRange* _tmp2_ = NULL;
	GeeTreeMapSubMap* _tmp3_ = NULL;
	GeeSortedMap* _tmp4_ = NULL;
	self = (GeeTreeMap*) base;
	_tmp0_ = before;
	_tmp1_ = gee_tree_map_range_new_head (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, self, _tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = gee_tree_map_sub_map_new (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, self, _tmp2_);
	_tmp4_ = (GeeSortedMap*) _tmp3_;
	_gee_tree_map_range_unref0 (_tmp2_);
	result = _tmp4_;
	return result;
}
