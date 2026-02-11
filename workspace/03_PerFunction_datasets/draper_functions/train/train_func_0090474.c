gee_concurrent_set_finalize (GObject* obj) {
	GeeConcurrentSet * self;
	GeeHazardPointerContext* ctx = NULL;
	GeeHazardPointerContext* _tmp0_ = NULL;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, GEE_TYPE_CONCURRENT_SET, GeeConcurrentSet);
	_tmp0_ = gee_hazard_pointer_context_new (NULL);
	ctx = _tmp0_;
	_gee_concurrent_set_tower_unref0 (self->priv->_head);
	self->priv->_head = NULL;
	_gee_hazard_pointer_context_free0 (ctx);
	_gee_concurrent_set_tower_unref0 (self->priv->_head);
	(self->priv->_cmp_target_destroy_notify == NULL) ? NULL : (self->priv->_cmp_target_destroy_notify (self->priv->_cmp_target), NULL);
	self->priv->_cmp = NULL;
	self->priv->_cmp_target = NULL;
	self->priv->_cmp_target_destroy_notify = NULL;
	G_OBJECT_CLASS (gee_concurrent_set_parent_class)->finalize (obj);
}
