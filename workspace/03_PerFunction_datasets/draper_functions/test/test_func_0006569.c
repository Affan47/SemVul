unity_deprecated_scope_base_get_impl (UnityDeprecatedScopeBase* self) {
	GObject* result = NULL;
	UnityInternalDeprecatedScopeDBusImpl* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_pimpl;
	result = (GObject*) _tmp0_;
	return result;
}
