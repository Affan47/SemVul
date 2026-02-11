gee_tree_map_node_iterator_has_next (GeeTreeMapNodeIterator* self) {
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	GeeTreeMap* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	gboolean _tmp5_ = FALSE;
	gboolean _tmp6_ = FALSE;
	gboolean _tmp7_ = FALSE;
	GeeTreeMapNode* _tmp8_ = NULL;
	gboolean _tmp10_ = FALSE;
	gboolean _tmp12_ = FALSE;
	gboolean _tmp15_ = FALSE;
	gboolean _tmp20_ = FALSE;
	gboolean _tmp26_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->stamp;
	_tmp1_ = self->_map;
	_tmp2_ = _tmp1_->priv->stamp;
	_vala_assert (_tmp0_ == _tmp2_, "stamp == _map.stamp");
	_tmp8_ = self->current;
	if (_tmp8_ == NULL) {
		GeeTreeMapNode* _tmp9_ = NULL;
		_tmp9_ = self->_next;
		_tmp7_ = _tmp9_ == NULL;
	} else {
		_tmp7_ = FALSE;
	}
	_tmp10_ = _tmp7_;
	if (_tmp10_) {
		GeeTreeMapNode* _tmp11_ = NULL;
		_tmp11_ = self->_prev;
		_tmp6_ = _tmp11_ == NULL;
	} else {
		_tmp6_ = FALSE;
	}
	_tmp12_ = _tmp6_;
	if (_tmp12_) {
		GeeTreeMap* _tmp13_ = NULL;
		GeeTreeMapNode* _tmp14_ = NULL;
		_tmp13_ = self->_map;
		_tmp14_ = _tmp13_->priv->first;
		_tmp5_ = _tmp14_ != NULL;
	} else {
		_tmp5_ = FALSE;
	}
	_tmp15_ = _tmp5_;
	if (_tmp15_) {
		_tmp4_ = TRUE;
	} else {
		gboolean _tmp16_ = FALSE;
		GeeTreeMapNode* _tmp17_ = NULL;
		gboolean _tmp19_ = FALSE;
		_tmp17_ = self->current;
		if (_tmp17_ == NULL) {
			GeeTreeMapNode* _tmp18_ = NULL;
			_tmp18_ = self->_next;
			_tmp16_ = _tmp18_ != NULL;
		} else {
			_tmp16_ = FALSE;
		}
		_tmp19_ = _tmp16_;
		_tmp4_ = _tmp19_;
	}
	_tmp20_ = _tmp4_;
	if (_tmp20_) {
		_tmp3_ = TRUE;
	} else {
		gboolean _tmp21_ = FALSE;
		GeeTreeMapNode* _tmp22_ = NULL;
		gboolean _tmp25_ = FALSE;
		_tmp22_ = self->current;
		if (_tmp22_ != NULL) {
			GeeTreeMapNode* _tmp23_ = NULL;
			GeeTreeMapNode* _tmp24_ = NULL;
			_tmp23_ = self->current;
			_tmp24_ = _tmp23_->next;
			_tmp21_ = _tmp24_ != NULL;
		} else {
			_tmp21_ = FALSE;
		}
		_tmp25_ = _tmp21_;
		_tmp3_ = _tmp25_;
	}
	_tmp26_ = _tmp3_;
	result = _tmp26_;
	return result;
}
