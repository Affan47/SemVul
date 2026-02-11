gee_hash_map_finalize (GObject* obj) {
	GeeHashMap * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, GEE_TYPE_HASH_MAP, GeeHashMap);
	gee_abstract_map_clear ((GeeAbstractMap*) self);
	(self->priv->_key_hash_func_target_destroy_notify == NULL) ? NULL : (self->priv->_key_hash_func_target_destroy_notify (self->priv->_key_hash_func_target), NULL);
	self->priv->_key_hash_func = NULL;
	self->priv->_key_hash_func_target = NULL;
	self->priv->_key_hash_func_target_destroy_notify = NULL;
	(self->priv->_key_equal_func_target_destroy_notify == NULL) ? NULL : (self->priv->_key_equal_func_target_destroy_notify (self->priv->_key_equal_func_target), NULL);
	self->priv->_key_equal_func = NULL;
	self->priv->_key_equal_func_target = NULL;
	self->priv->_key_equal_func_target_destroy_notify = NULL;
	(self->priv->_value_equal_func_target_destroy_notify == NULL) ? NULL : (self->priv->_value_equal_func_target_destroy_notify (self->priv->_value_equal_func_target), NULL);
	self->priv->_value_equal_func = NULL;
	self->priv->_value_equal_func_target = NULL;
	self->priv->_value_equal_func_target_destroy_notify = NULL;
	self->priv->_nodes = (_vala_array_free (self->priv->_nodes, self->priv->_nodes_length1, (GDestroyNotify) gee_hash_map_node_free), NULL);
	G_OBJECT_CLASS (gee_hash_map_parent_class)->finalize (obj);
}
