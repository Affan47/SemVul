gee_tree_set_real_remove (GeeAbstractCollection* base, gconstpointer item) {
	GeeTreeSet * self;
	gboolean result = FALSE;
	gboolean b = FALSE;
	gconstpointer _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	GeeTreeSetNode* _tmp2_ = NULL;
	gint _tmp4_ = 0;
	self = (GeeTreeSet*) base;
	_tmp0_ = item;
	_tmp1_ = gee_tree_set_remove_from_node (self, &self->priv->root, _tmp0_, NULL, NULL);
	b = _tmp1_;
	_tmp2_ = self->priv->root;
	if (_tmp2_ != NULL) {
		GeeTreeSetNode* _tmp3_ = NULL;
		_tmp3_ = self->priv->root;
		_tmp3_->color = GEE_TREE_SET_NODE_COLOR_BLACK;
	}
	_tmp4_ = self->priv->stamp;
	self->priv->stamp = _tmp4_ + 1;
	result = b;
	return result;
}
