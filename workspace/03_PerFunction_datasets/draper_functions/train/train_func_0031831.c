mm_keys_finalize (GObject* obj) {
	MMKeys * self;
	gboolean _tmp0_;
	GError * _inner_error_ = NULL;
	self = MM_KEYS (obj);
	_tmp0_ = gmpc_plugin_base_get_enabled ((GmpcPluginBase*) self);
	if (_tmp0_) {
		media_keys_ReleaseMediaPlayerKeys (self->priv->keys, "gmpc", &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
		goto __finally0;
		__catch0_dbus_gerror:
		{
			GError * _error_;
			_error_ = _inner_error_;
			_inner_error_ = NULL;
			g_warning ("mmkeys.vala:96: Failed to release media keys: %s\n", _error_->message);
			_g_error_free0 (_error_);
		}
		__finally0:
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
	}
	_dbus_g_connection_unref0 (self->priv->conn);
	_g_object_unref0 (self->priv->keys);
	G_OBJECT_CLASS (mm_keys_parent_class)->finalize (obj);
}
