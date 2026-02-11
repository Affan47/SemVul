gnome_chess_app_configure_event_cb (GtkWidget* widget, GdkEventConfigure* event, Application* self) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	GSettings* _tmp1_;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp5_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp1_ = self->priv->settings;
	_tmp2_ = g_settings_get_boolean (_tmp1_, "maximized");
	if (!_tmp2_) {
		GSettings* _tmp3_;
		gboolean _tmp4_ = FALSE;
		_tmp3_ = self->priv->settings;
		_tmp4_ = g_settings_get_boolean (_tmp3_, "fullscreen");
		_tmp0_ = !_tmp4_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	if (_tmp5_) {
		GSettings* _tmp6_;
		GdkEventConfigure _tmp7_;
		gint _tmp8_;
		GSettings* _tmp9_;
		GdkEventConfigure _tmp10_;
		gint _tmp11_;
		_tmp6_ = self->priv->settings;
		_tmp7_ = *event;
		_tmp8_ = _tmp7_.width;
		g_settings_set_int (_tmp6_, "width", _tmp8_);
		_tmp9_ = self->priv->settings;
		_tmp10_ = *event;
		_tmp11_ = _tmp10_.height;
		g_settings_set_int (_tmp9_, "height", _tmp11_);
	}
	result = FALSE;
	return result;
}
