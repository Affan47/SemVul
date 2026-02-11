gee_tree_map_sub_entry_set_set_map (GeeTreeMapSubEntrySet* self, GeeTreeMap* value) {
	GeeTreeMap* _tmp0_ = NULL;
	GeeTreeMap* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_map);
	self->priv->_map = _tmp1_;
}
