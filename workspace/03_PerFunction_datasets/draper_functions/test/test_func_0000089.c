___lambda6_ (UnityInternalDeprecatedScopeImpl* self) {
	gboolean result = FALSE;
	GVariant* invalidated = NULL;
	GVariantType* _tmp0_ = NULL;
	GVariantType* _tmp1_ = NULL;
	GVariant** _tmp2_ = NULL;
	GVariant** _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	GVariant* _tmp4_ = NULL;
	GVariant* _tmp5_ = NULL;
	GError * _inner_error_ = NULL;
	_tmp0_ = g_variant_type_new ("s");
	_tmp1_ = _tmp0_;
	_tmp2_ = g_new0 (GVariant*, 0 + 1);
	_tmp3_ = _tmp2_;
	_tmp3__length1 = 0;
	_tmp4_ = g_variant_new_array (_tmp1_, _tmp3_, 0);
	g_variant_ref_sink (_tmp4_);
	_tmp5_ = _tmp4_;
	_tmp3_ = (_vala_array_free (_tmp3_, _tmp3__length1, (GDestroyNotify) g_variant_unref), NULL);
	_g_variant_type_free0 (_tmp1_);
	invalidated = _tmp5_;
	{
		GDBusConnection* _tmp6_ = NULL;
		UnityDeprecatedScope* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		GVariantBuilder* _tmp10_ = NULL;
		GVariant* _tmp11_ = NULL;
		GVariant* _tmp12_ = NULL;
		_tmp6_ = self->priv->_dbus_connection;
		_tmp7_ = self->priv->_owner;
		_tmp8_ = unity_deprecated_scope_base_get_dbus_path ((UnityDeprecatedScopeBase*) _tmp7_);
		_tmp9_ = _tmp8_;
		_tmp10_ = self->priv->changed_props;
		_tmp11_ = g_variant_new ("(sa{sv}@as)", UNITY_PROTOCOL_SCOPE_SERVICE_INTERFACE_NAME, _tmp10_, invalidated, NULL);
		g_variant_ref_sink (_tmp11_);
		_tmp12_ = _tmp11_;
		g_dbus_connection_emit_signal (_tmp6_, NULL, _tmp9_, "org.freedesktop.DBus.Properties", "PropertiesChanged", _tmp12_, &_inner_error_);
		_g_variant_unref0 (_tmp12_);
		if (_inner_error_ != NULL) {
			goto __catch22_g_error;
		}
	}
	goto __finally22;
	__catch22_g_error:
	{
		GError* err = NULL;
		GError* _tmp13_ = NULL;
		const gchar* _tmp14_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp13_ = err;
		_tmp14_ = _tmp13_->message;
		g_warning ("unity-deprecated-scope-impl.vala:146: %s", _tmp14_);
		_g_error_free0 (err);
	}
	__finally22:
	if (_inner_error_ != NULL) {
		_g_variant_unref0 (invalidated);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	_g_variant_builder_unref0 (self->priv->changed_props);
	self->priv->changed_props = NULL;
	result = FALSE;
	_g_variant_unref0 (invalidated);
	return result;
}
