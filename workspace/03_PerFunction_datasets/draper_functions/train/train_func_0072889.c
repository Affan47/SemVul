unity_internal_default_scope_dbus_impl_real_dispose (GObject* base) {
	UnityInternalDefaultScopeDBusImpl * self;
	guint _tmp0_ = 0U;
	guint _tmp2_ = 0U;
	self = (UnityInternalDefaultScopeDBusImpl*) base;
	_tmp0_ = self->priv->_inactivity_timeout_source_id;
	if (_tmp0_ != ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = self->priv->_inactivity_timeout_source_id;
		g_source_remove (_tmp1_);
		self->priv->_inactivity_timeout_source_id = (guint) 0;
	}
	_tmp2_ = self->priv->_unexport_timeout_source_id;
	if (_tmp2_ != ((guint) 0)) {
		guint _tmp3_ = 0U;
		_tmp3_ = self->priv->_unexport_timeout_source_id;
		g_source_remove (_tmp3_);
		self->priv->_unexport_timeout_source_id = (guint) 0;
	}
}
