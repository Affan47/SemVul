gee_tree_map_real_sub_map (GeeAbstractSortedMap* base, gconstpointer after, gconstpointer before) {
	GeeTreeMap * self;
	GeeSortedMap* result = NULL;
	gconstpointer _tmp0_ = NULL;
	gconstpointer _tmp1_ = NULL;
	GeeTreeMapRange* _tmp2_ = NULL;
	GeeTreeMapRange* _tmp3_ = NULL;
	GeeTreeMapSubMap* _tmp4_ = NULL;
	GeeSortedMap* _tmp5_ = NULL;
	self = (GeeTreeMap*) base;
	_tmp0_ = after;
	_tmp1_ = before;
	_tmp2_ = gee_tree_map_range_new (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, self, _tmp0_, _tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = gee_tree_map_sub_map_new (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, self, _tmp3_);
	_tmp5_ = (GeeSortedMap*) _tmp4_;
	_gee_tree_map_range_unref0 (_tmp3_);
	result = _tmp5_;
	return result;
}
