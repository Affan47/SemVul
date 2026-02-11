gee_hash_multi_map_finalize (GObject* obj) {
	GeeHashMultiMap * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, GEE_TYPE_HASH_MULTI_MAP, GeeHashMultiMap);
	(self->priv->_value_hash_func_target_destroy_notify == NULL) ? NULL : (self->priv->_value_hash_func_target_destroy_notify (self->priv->_value_hash_func_target), NULL);
	self->priv->_value_hash_func = NULL;
	self->priv->_value_hash_func_target = NULL;
	self->priv->_value_hash_func_target_destroy_notify = NULL;
	(self->priv->_value_equal_func_target_destroy_notify == NULL) ? NULL : (self->priv->_value_equal_func_target_destroy_notify (self->priv->_value_equal_func_target), NULL);
	self->priv->_value_equal_func = NULL;
	self->priv->_value_equal_func_target = NULL;
	self->priv->_value_equal_func_target_destroy_notify = NULL;
	G_OBJECT_CLASS (gee_hash_multi_map_parent_class)->finalize (obj);
}
