file_browser_monitor_directory (FileBrowser* self) {
	GFile* _tmp0_ = NULL;
	GFileMonitor* _tmp7_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_current_directory;
	if (_tmp0_ == NULL) {
		_g_object_unref0 (self->priv->_monitor);
		self->priv->_monitor = NULL;
		return;
	}
	{
		GFileMonitor* _tmp1_ = NULL;
		GFile* _tmp2_ = NULL;
		GFileMonitor* _tmp3_ = NULL;
		GFileMonitor* _tmp4_ = NULL;
		_tmp2_ = self->priv->_current_directory;
		_tmp3_ = g_file_monitor_directory (_tmp2_, G_FILE_MONITOR_NONE, NULL, &_inner_error_);
		_tmp1_ = _tmp3_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch30_g_io_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		_tmp4_ = _tmp1_;
		_tmp1_ = NULL;
		_g_object_unref0 (self->priv->_monitor);
		self->priv->_monitor = _tmp4_;
		_g_object_unref0 (_tmp1_);
	}
	goto __finally30;
	__catch30_g_io_error:
	{
		GError* e = NULL;
		GError* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp5_ = e;
		_tmp6_ = _tmp5_->message;
		g_warning ("file_browser.vala:487: Can not refresh automatically the file browser:" \
" %s", _tmp6_);
		_g_error_free0 (e);
		return;
	}
	__finally30:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp7_ = self->priv->_monitor;
	g_signal_connect_object (_tmp7_, "changed", (GCallback) _file_browser_refresh_g_file_monitor_changed, self, 0);
}
