caribou_scanner_on_level_changed (CaribouScanner* self, GObject* obj, GParamSpec* prop) {
	CaribouGroupModel* group = NULL;
	GObject* _tmp0_ = NULL;
	CaribouGroupModel* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	CaribouLevelModel* _tmp4_ = NULL;
	CaribouLevelModel* _tmp5_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (obj != NULL);
	g_return_if_fail (prop != NULL);
	_tmp0_ = obj;
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, CARIBOU_TYPE_GROUP_MODEL, CaribouGroupModel));
	group = _tmp1_;
	_tmp2_ = caribou_group_model_get_active_level (group);
	_tmp3_ = _tmp2_;
	_tmp4_ = caribou_group_model_get_level (group, _tmp3_);
	_tmp5_ = _tmp4_;
	caribou_scanner_set_active_level (self, _tmp5_);
	_g_object_unref0 (_tmp5_);
	_g_object_unref0 (group);
}
