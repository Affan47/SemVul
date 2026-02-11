structure_model_real_iter_n_children (GtkTreeModel* base, GtkTreeIter* iter) {
	StructureModel * self;
	gint result = 0;
	GNode* node = NULL;
	GtkTreeIter* _tmp0_ = NULL;
	GNode* _tmp8_ = NULL;
	guint _tmp9_ = 0U;
	self = (StructureModel*) base;
	_tmp0_ = iter;
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
		_tmp2_ = iter;
		_tmp3_ = *_tmp2_;
		_tmp4_ = structure_model_iter_is_valid (self, &_tmp3_);
		g_return_val_if_fail (_tmp4_, -1);
		_tmp5_ = iter;
		_tmp6_ = *_tmp5_;
		_tmp7_ = structure_model_get_node_from_iter (self, &_tmp6_);
		node = _tmp7_;
	}
	_tmp8_ = node;
	_tmp9_ = g_node_n_children (_tmp8_);
	result = (gint) _tmp9_;
	return result;
}
