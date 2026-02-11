unity_internal_deprecated_scope_impl_real_unexport (UnityInternalScopeDBusImpl* base) {
	UnityInternalDeprecatedScopeImpl * self;
	guint _tmp0_ = 0U;
	self = (UnityInternalDeprecatedScopeImpl*) base;
	_tmp0_ = self->priv->_dbus_id;
	if (_tmp0_ != ((guint) 0)) {
		GDBusConnection* _tmp1_ = NULL;
		guint _tmp2_ = 0U;
		_tmp1_ = self->priv->_dbus_connection;
		_tmp2_ = self->priv->_dbus_id;
		g_dbus_connection_unregister_object (_tmp1_, _tmp2_);
		self->priv->_dbus_id = (guint) 0;
		_g_object_unref0 (self->priv->_dbus_connection);
		self->priv->_dbus_connection = NULL;
	}
}
