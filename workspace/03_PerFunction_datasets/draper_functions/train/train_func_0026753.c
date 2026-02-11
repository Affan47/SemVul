structure_model_real_iter_nth_child (GtkTreeModel* base, GtkTreeIter* iter, GtkTreeIter* parent, gint n) {
	StructureModel * self;
	GtkTreeIter _vala_iter = {0};
	gboolean result = FALSE;
	GNode* node = NULL;
	GtkTreeIter* _tmp0_ = NULL;
	GNode* _tmp8_ = NULL;
	gboolean _tmp9_ = FALSE;
	gboolean _tmp10_ = FALSE;
	gint _tmp11_ = 0;
	GNode* _tmp15_ = NULL;
	gint _tmp16_ = 0;
	GNode* _tmp17_ = NULL;
	GtkTreeIter* _tmp18_ = NULL;
	GtkTreeIter* _tmp19_ = NULL;
	self = (StructureModel*) base;
	memset (&_vala_iter, 0, sizeof (GtkTreeIter));
	_tmp0_ = parent;
	if (_tmp0_ == NULL) {
		GNode* _tmp1_ = NULL;
		_tmp1_ = self->priv->_tree;
		node = _tmp1_;
	} else {
		GtkTreeIter* _tmp2_ = NULL;
		GtkTreeIter _tmp3_ = {0};
		gboolean _tmp4_ = FALSE;
		GtkTreeIter* _tmp5_ = NULL;
		GtkTreeIter _tmp6_ = {0};
		GNode* _tmp7_ = NULL;
		_tmp2_ = parent;
		_tmp3_ = *_tmp2_;
		_tmp4_ = structure_model_iter_is_valid (self, &_tmp3_);
		g_return_val_if_fail (_tmp4_, FALSE);
		_tmp5_ = parent;
		_tmp6_ = *_tmp5_;
		_tmp7_ = structure_model_get_node_from_iter (self, &_tmp6_);
		node = _tmp7_;
	}
	_tmp8_ = node;
	_tmp9_ = G_NODE_IS_LEAF (_tmp8_);
	if (_tmp9_) {
		result = FALSE;
		if (iter) {
			*iter = _vala_iter;
		}
		return result;
	}
	_tmp11_ = n;
	if (_tmp11_ < 0) {
		_tmp10_ = TRUE;
	} else {
		GNode* _tmp12_ = NULL;
		guint _tmp13_ = 0U;
		gint _tmp14_ = 0;
		_tmp12_ = node;
		_tmp13_ = g_node_n_children (_tmp12_);
		_tmp14_ = n;
		_tmp10_ = _tmp13_ <= ((guint) _tmp14_);
	}
	if (_tmp10_) {
		result = FALSE;
		if (iter) {
			*iter = _vala_iter;
		}
		return result;
	}
	_tmp15_ = node;
	_tmp16_ = n;
	_tmp17_ = g_node_nth_child (_tmp15_, (guint) _tmp16_);
	_tmp18_ = structure_model_create_iter_at_node (self, _tmp17_);
	_tmp19_ = _tmp18_;
	_vala_iter = *_tmp19_;
	_g_free0 (_tmp19_);
	result = TRUE;
	if (iter) {
		*iter = _vala_iter;
	}
	return result;
}
