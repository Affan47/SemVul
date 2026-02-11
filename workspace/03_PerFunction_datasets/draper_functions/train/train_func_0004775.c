gee_tree_map_sub_entry_set_real_iterator_at (GeeAbstractSortedSet* base, GeeMapEntry* entry) {
	GeeTreeMapSubEntrySet * self;
	GeeIterator* result = NULL;
	GeeTreeMapRange* _tmp0_ = NULL;
	GeeMapEntry* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	gconstpointer _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	GeeTreeMapNode* n = NULL;
	GeeTreeMap* _tmp5_ = NULL;
	GeeMapEntry* _tmp6_ = NULL;
	gconstpointer _tmp7_ = NULL;
	gconstpointer _tmp8_ = NULL;
	GeeTreeMapNode* _tmp9_ = NULL;
	gboolean _tmp10_ = FALSE;
	GeeTreeMapNode* _tmp11_ = NULL;
	gboolean _tmp21_ = FALSE;
	GeeTreeMap* _tmp22_ = NULL;
	GeeTreeMapRange* _tmp23_ = NULL;
	GeeTreeMapNode* _tmp24_ = NULL;
	GeeTreeMapSubEntryIterator* _tmp25_ = NULL;
	self = (GeeTreeMapSubEntrySet*) base;
	g_return_val_if_fail (entry != NULL, NULL);
	_tmp0_ = self->priv->_range;
	_tmp1_ = entry;
	_tmp2_ = gee_map_entry_get_key (_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = gee_tree_map_range_in_range (_tmp0_, _tmp3_);
	if (!_tmp4_) {
		result = NULL;
		return result;
	}
	_tmp5_ = self->priv->_map;
	_tmp6_ = entry;
	_tmp7_ = gee_map_entry_get_key (_tmp6_);
	_tmp8_ = _tmp7_;
	_tmp9_ = gee_tree_map_find_node (_tmp5_, _tmp8_);
	n = _tmp9_;
	_tmp11_ = n;
	if (_tmp11_ == NULL) {
		_tmp10_ = TRUE;
	} else {
		GeeTreeMap* _tmp12_ = NULL;
		GeeEqualDataFunc _tmp13_ = NULL;
		void* _tmp13__target = NULL;
		GeeEqualDataFunc _tmp14_ = NULL;
		void* _tmp14__target = NULL;
		GeeTreeMapNode* _tmp15_ = NULL;
		gconstpointer _tmp16_ = NULL;
		GeeMapEntry* _tmp17_ = NULL;
		gconstpointer _tmp18_ = NULL;
		gconstpointer _tmp19_ = NULL;
		gboolean _tmp20_ = FALSE;
		_tmp12_ = self->priv->_map;
		_tmp13_ = gee_tree_map_get_value_equal_func (_tmp12_, &_tmp13__target);
		_tmp14_ = _tmp13_;
		_tmp14__target = _tmp13__target;
		_tmp15_ = n;
		_tmp16_ = _tmp15_->value;
		_tmp17_ = entry;
		_tmp18_ = gee_map_entry_get_value (_tmp17_);
		_tmp19_ = _tmp18_;
		_tmp20_ = _tmp14_ (_tmp16_, _tmp19_, _tmp14__target);
		_tmp10_ = !_tmp20_;
	}
	_tmp21_ = _tmp10_;
	if (_tmp21_) {
		result = NULL;
		return result;
	}
	_tmp22_ = self->priv->_map;
	_tmp23_ = self->priv->_range;
	_tmp24_ = n;
	_tmp25_ = gee_tree_map_sub_entry_iterator_new_pointing (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, _tmp22_, _tmp23_, _tmp24_);
	result = (GeeIterator*) _tmp25_;
	return result;
}
