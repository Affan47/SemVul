gee_lazy_finalize (GeeLazy* obj) {
	GeeLazy * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, GEE_TYPE_LAZY, GeeLazy);
	(self->priv->_func_target_destroy_notify == NULL) ? NULL : (self->priv->_func_target_destroy_notify (self->priv->_func_target), NULL);
	self->priv->_func = NULL;
	self->priv->_func_target = NULL;
	self->priv->_func_target_destroy_notify = NULL;
	((self->priv->_value == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (self->priv->_value = (self->priv->g_destroy_func (self->priv->_value), NULL));
}
