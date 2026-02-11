gee_tree_map_sub_node_iterator_real_iterator_pointing_at (GeeTreeMapSubNodeIterator* self, GeeTreeMapNode* node) {
	GeeTreeMapNodeIterator* result = NULL;
	GeeTreeMap* _tmp0_ = NULL;
	GeeTreeMapNode* _tmp1_ = NULL;
	GeeTreeMapNodeIterator* _tmp2_ = NULL;
	g_return_val_if_fail (node != NULL, NULL);
	_tmp0_ = self->_map;
	_tmp1_ = node;
	_tmp2_ = gee_tree_map_node_iterator_new_pointing (self->priv->k_type, (GBoxedCopyFunc) self->priv->k_dup_func, self->priv->k_destroy_func, self->priv->v_type, (GBoxedCopyFunc) self->priv->v_dup_func, self->priv->v_destroy_func, _tmp0_, _tmp1_);
	result = _tmp2_;
	return result;
}
