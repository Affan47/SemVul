gee_tree_map_sub_node_iterator_finalize (GObject* obj) {
	GeeTreeMapSubNodeIterator * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, GEE_TREE_MAP_TYPE_SUB_NODE_ITERATOR, GeeTreeMapSubNodeIterator);
	_g_object_unref0 (self->_map);
	_gee_tree_map_range_unref0 (self->range);
	_g_object_unref0 (self->iterator);
	G_OBJECT_CLASS (gee_tree_map_sub_node_iterator_parent_class)->finalize (obj);
}
