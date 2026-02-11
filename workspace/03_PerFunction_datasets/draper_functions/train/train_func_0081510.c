gee_tree_map_sub_map_real_unset (GeeAbstractMap* base, gconstpointer key, gpointer* value) {
	GeeTreeMapSubMap * self;
	gpointer _vala_value = NULL;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	GeeTreeMapRange* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp8_ = FALSE;
	self = (GeeTreeMapSubMap*) base;
	((_vala_value == NULL) || (self->priv->v_destroy_func == NULL)) ? NULL : (_vala_value = (self->priv->v_destroy_func (_vala_value), NULL));
	_vala_value = NULL;
	_tmp1_ = self->priv->range;
	_tmp2_ = key;
	_tmp3_ = gee_tree_map_range_in_range (_tmp1_, _tmp2_);
	if (_tmp3_) {
		GeeTreeMap* _tmp4_ = NULL;
		gconstpointer _tmp5_ = NULL;
		gpointer _tmp6_ = NULL;
		gboolean _tmp7_ = FALSE;
		_tmp4_ = self->priv->map;
		_tmp5_ = key;
		_tmp7_ = gee_abstract_map_unset ((GeeAbstractMap*) _tmp4_, _tmp5_, &_tmp6_);
		((_vala_value == NULL) || (self->priv->v_destroy_func == NULL)) ? NULL : (_vala_value = (self->priv->v_destroy_func (_vala_value), NULL));
		_vala_value = _tmp6_;
		_tmp0_ = _tmp7_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp8_ = _tmp0_;
	result = _tmp8_;
	if (value) {
		*value = _vala_value;
	} else {
		((_vala_value == NULL) || (self->priv->v_destroy_func == NULL)) ? NULL : (_vala_value = (self->priv->v_destroy_func (_vala_value), NULL));
	}
	return result;
}
