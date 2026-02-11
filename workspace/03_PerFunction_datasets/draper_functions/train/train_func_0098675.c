diodon_plugins_indicator_plugin_real_deactivate (PeasActivatable* base) {
	DiodonPluginsIndicatorPlugin * self;
	AppIndicator* _tmp0_ = NULL;
	self = (DiodonPluginsIndicatorPlugin*) base;
	_tmp0_ = self->priv->indicator;
	if (_tmp0_ != NULL) {
		AppIndicator* _tmp1_ = NULL;
		_tmp1_ = self->priv->indicator;
		app_indicator_set_status (_tmp1_, APP_INDICATOR_STATUS_PASSIVE);
	}
}
