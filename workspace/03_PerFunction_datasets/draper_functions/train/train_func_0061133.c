caribou_scannable_group_get_stepping_child (CaribouScannableGroup* self) {
	CaribouIScannableItem* result = NULL;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	CaribouIScannableItem** _tmp2_ = NULL;
	CaribouIScannableItem** _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	gint _tmp4_ = 0;
	CaribouIScannableItem* _tmp5_ = NULL;
	CaribouIScannableItem* _tmp6_ = NULL;
	CaribouIScannableItem* _tmp7_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_scan_child_index;
	if (_tmp0_ < 0) {
		result = NULL;
		return result;
	}
	_tmp2_ = caribou_scannable_group_get_scan_children (self, &_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp3__length1 = _tmp1_;
	_tmp4_ = self->priv->_scan_child_index;
	_tmp5_ = _tmp3_[_tmp4_];
	_tmp6_ = _g_object_ref0 (_tmp5_);
	_tmp7_ = _tmp6_;
	_tmp3_ = (_vala_array_free (_tmp3_, _tmp3__length1, (GDestroyNotify) g_object_unref), NULL);
	result = _tmp7_;
	return result;
}
