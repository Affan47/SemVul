gee_tree_map_sub_node_iterator_next (GeeTreeMapSubNodeIterator* self) {
	gboolean result = FALSE;
	GeeTreeMapNodeIterator* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->iterator;
	if (_tmp0_ != NULL) {
		GeeTreeMapNode* node = NULL;
		GeeTreeMapNodeIterator* _tmp1_ = NULL;
		GeeTreeMapNode* _tmp2_ = NULL;
		gboolean _tmp3_ = FALSE;
		GeeTreeMapNode* _tmp4_ = NULL;
		gboolean _tmp9_ = FALSE;
		_tmp1_ = self->iterator;
		_tmp2_ = gee_tree_map_node_iterator_safe_next_get (_tmp1_);
		node = _tmp2_;
		_tmp4_ = node;
		if (_tmp4_ != NULL) {
			GeeTreeMapRange* _tmp5_ = NULL;
			GeeTreeMapNode* _tmp6_ = NULL;
			gconstpointer _tmp7_ = NULL;
			gboolean _tmp8_ = FALSE;
			_tmp5_ = self->range;
			_tmp6_ = node;
			_tmp7_ = _tmp6_->key;
			_tmp8_ = gee_tree_map_range_in_range (_tmp5_, _tmp7_);
			_tmp3_ = _tmp8_;
		} else {
			_tmp3_ = FALSE;
		}
		_tmp9_ = _tmp3_;
		if (_tmp9_) {
			GeeTreeMapNodeIterator* _tmp10_ = NULL;
			gboolean _tmp11_ = FALSE;
			_tmp10_ = self->iterator;
			_tmp11_ = gee_tree_map_node_iterator_next (_tmp10_);
			_vala_assert (_tmp11_, "iterator.next ()");
			result = TRUE;
			return result;
		} else {
			result = FALSE;
			return result;
		}
	} else {
		gboolean _tmp12_ = FALSE;
		_tmp12_ = gee_tree_map_sub_node_iterator_first (self);
		result = _tmp12_;
		return result;
	}
}
