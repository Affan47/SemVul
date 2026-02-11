indicator_keyboard_service_handle_unity_name_appeared (IndicatorKeyboardService* self, GDBusConnection* connection, const gchar* name, const gchar* name_owner) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (connection != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (name_owner != NULL);
	{
		UnitySession* _tmp0_ = NULL;
		const gchar* _tmp1_ = NULL;
		UnitySession* _tmp2_ = NULL;
		UnitySession* _tmp3_ = NULL;
		UnitySession* _tmp4_ = NULL;
		_tmp1_ = name;
		_tmp2_ = g_initable_new (TYPE_UNITY_SESSION_PROXY, NULL, &_inner_error_, "g-flags", 0, "g-name", _tmp1_, "g-bus-type", G_BUS_TYPE_SESSION, "g-object-path", "/com/canonical/Unity/Session", "g-interface-name", "com.canonical.Unity.Session", NULL);
		_tmp0_ = (UnitySession*) _tmp2_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch11_g_io_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		_g_object_unref0 (self->priv->unity_session);
		self->priv->unity_session = _tmp0_;
		_tmp3_ = self->priv->unity_session;
		g_signal_connect_object (G_TYPE_CHECK_INSTANCE_CAST (_tmp3_, TYPE_UNITY_SESSION, UnitySession), "locked", (GCallback) ____lambda20__unity_session_locked, self, 0);
		_tmp4_ = self->priv->unity_session;
		g_signal_connect_object (G_TYPE_CHECK_INSTANCE_CAST (_tmp4_, TYPE_UNITY_SESSION, UnitySession), "unlocked", (GCallback) ____lambda21__unity_session_unlocked, self, 0);
	}
	goto __finally11;
	__catch11_g_io_error:
	{
		GError* _error_ = NULL;
		GError* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		_tmp5_ = _error_;
		_tmp6_ = _tmp5_->message;
		g_warning ("main.vala:1057: error: %s", _tmp6_);
		_g_error_free0 (_error_);
	}
	__finally11:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
