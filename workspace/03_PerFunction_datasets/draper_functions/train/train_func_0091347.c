caribou_group_model_add_level (CaribouGroupModel* self, const gchar* lname, CaribouLevelModel* level) {
	GeeHashMap* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	CaribouLevelModel* _tmp2_ = NULL;
	CaribouLevelModel* _tmp3_ = NULL;
	CaribouLevelModel* _tmp4_ = NULL;
	CaribouLevelModel* _tmp5_ = NULL;
	CaribouLevelModel* _tmp6_ = NULL;
	CaribouLevelModel* _tmp7_ = NULL;
	const gchar* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (lname != NULL);
	g_return_if_fail (level != NULL);
	_tmp0_ = self->priv->levels;
	_tmp1_ = lname;
	_tmp2_ = level;
	gee_abstract_map_set ((GeeAbstractMap*) _tmp0_, _tmp1_, _tmp2_);
	_tmp3_ = level;
	g_signal_connect_object (_tmp3_, "level-toggled", (GCallback) _caribou_group_model_on_level_toggled_caribou_level_model_level_toggled, self, 0);
	_tmp4_ = level;
	g_signal_connect_object ((CaribouIKeyboardObject*) _tmp4_, "key-clicked", (GCallback) ___lambda11__caribou_ikeyboard_object_key_clicked, self, 0);
	_tmp5_ = level;
	g_signal_connect_object ((CaribouIKeyboardObject*) _tmp5_, "key-pressed", (GCallback) ___lambda12__caribou_ikeyboard_object_key_pressed, self, 0);
	_tmp6_ = level;
	g_signal_connect_object ((CaribouIKeyboardObject*) _tmp6_, "key-released", (GCallback) ___lambda13__caribou_ikeyboard_object_key_released, self, 0);
	_tmp7_ = level;
	_tmp8_ = caribou_level_model_get_mode (_tmp7_);
	_tmp9_ = _tmp8_;
	if (g_strcmp0 (_tmp9_, "default") == 0) {
		const gchar* _tmp10_ = NULL;
		gchar* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		_tmp10_ = lname;
		_tmp11_ = g_strdup (_tmp10_);
		_g_free0 (self->priv->default_level);
		self->priv->default_level = _tmp11_;
		_tmp12_ = lname;
		caribou_group_model_set_active_level (self, _tmp12_);
	}
}
