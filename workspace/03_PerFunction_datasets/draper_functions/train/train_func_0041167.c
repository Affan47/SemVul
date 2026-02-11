___lambda21_ (IndicatorKeyboardService* self) {
	GAction* _tmp0_ = NULL;
	GAction* _tmp1_ = NULL;
	GSettings* _tmp2_ = NULL;
	GVariant* _tmp3_ = NULL;
	GVariant* _tmp4_ = NULL;
	_tmp0_ = indicator_keyboard_service_get_active_action (self);
	_tmp1_ = _tmp0_;
	_tmp2_ = self->priv->source_settings;
	_tmp3_ = g_settings_get_value (_tmp2_, "current");
	_tmp4_ = _tmp3_;
	g_action_change_state (_tmp1_, _tmp4_);
	_g_variant_unref0 (_tmp4_);
	_g_object_unref0 (_tmp1_);
}
