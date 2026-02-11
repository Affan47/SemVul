gee_lazy_eval (GeeLazy* self) {
	GeeLazyFunc _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_func;
	_tmp0__target = self->priv->_func_target;
	if (_tmp0_ != NULL) {
		GeeLazyFunc _tmp1_ = NULL;
		void* _tmp1__target = NULL;
		gpointer _tmp2_ = NULL;
		_tmp1_ = self->priv->_func;
		_tmp1__target = self->priv->_func_target;
		_tmp2_ = _tmp1_ (_tmp1__target);
		((self->priv->_value == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (self->priv->_value = (self->priv->g_destroy_func (self->priv->_value), NULL));
		self->priv->_value = _tmp2_;
		(self->priv->_func_target_destroy_notify == NULL) ? NULL : (self->priv->_func_target_destroy_notify (self->priv->_func_target), NULL);
		self->priv->_func = NULL;
		self->priv->_func_target = NULL;
		self->priv->_func_target_destroy_notify = NULL;
		self->priv->_func = NULL;
		self->priv->_func_target = NULL;
		self->priv->_func_target_destroy_notify = NULL;
	}
}
