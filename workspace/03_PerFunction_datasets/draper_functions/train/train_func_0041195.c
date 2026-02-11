bluez_reset_manager (Bluez* self) {
	gchar* new_adapter_path = NULL;
	const gchar* _tmp11_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	new_adapter_path = NULL;
	{
		orgbluezManager* _tmp0_ = NULL;
		GDBusConnection* _tmp1_ = NULL;
		orgbluezManager* _tmp2_ = NULL;
		orgbluezManager* _tmp3_ = NULL;
		orgbluezManager* _tmp4_ = NULL;
		char* _tmp5_ = NULL;
		orgbluezManager* _tmp6_ = NULL;
		char* _tmp7_ = NULL;
		_tmp1_ = self->priv->bus;
		_tmp2_ = g_initable_new (ORG_BLUEZ_TYPE_MANAGER_PROXY, NULL, &_inner_error_, "g-flags", 0, "g-name", "org.bluez", "g-connection", _tmp1_, "g-object-path", "/", "g-interface-name", "org.bluez.Manager", NULL);
		_tmp0_ = (orgbluezManager*) _tmp2_;
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
		_g_object_unref0 (self->priv->manager);
		self->priv->manager = _tmp0_;
		_tmp3_ = self->priv->manager;
		g_signal_connect_object (_tmp3_, "default-adapter-changed", (GCallback) ____lambda3__org_bluez_manager_default_adapter_changed, self, 0);
		_tmp4_ = self->priv->manager;
		g_signal_connect_object (_tmp4_, "adapter-removed", (GCallback) ____lambda8__org_bluez_manager_adapter_removed, self, 0);
		_tmp6_ = self->priv->manager;
		_tmp7_ = org_bluez_manager_default_adapter (_tmp6_, &_inner_error_);
		_tmp5_ = _tmp7_;
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
		_g_free0 (new_adapter_path);
		new_adapter_path = (gchar*) _tmp5_;
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError* e = NULL;
		GError* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		const gchar* _tmp10_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp8_ = e;
		_tmp9_ = _tmp8_->message;
		_tmp10_ = string_to_string (_tmp9_);
		g_critical ("bluez.vala:104: %s", _tmp10_);
		_g_error_free0 (e);
	}
	__finally1:
	if (_inner_error_ != NULL) {
		_g_free0 (new_adapter_path);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp11_ = new_adapter_path;
	bluez_on_default_adapter_changed (self, _tmp11_);
	_g_free0 (new_adapter_path);
}
