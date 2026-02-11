caribou_scannable_group_real_child_select (CaribouScannableGroup* self) {
	CaribouIScannableItem* result = NULL;
	CaribouIScannableItem* step_child = NULL;
	CaribouIScannableItem* _tmp0_ = NULL;
	CaribouIScannableItem* selected_leaf = NULL;
	GeeLinkedList* _tmp1_ = NULL;
	gpointer _tmp2_ = NULL;
	CaribouIScannableItem* _tmp3_ = NULL;
	GeeLinkedList* _tmp20_ = NULL;
	gpointer _tmp21_ = NULL;
	_tmp0_ = caribou_scannable_group_get_stepping_child (self);
	step_child = _tmp0_;
	_tmp1_ = self->priv->_selected_path;
	_tmp2_ = gee_deque_peek_tail ((GeeDeque*) _tmp1_);
	selected_leaf = (CaribouIScannableItem*) _tmp2_;
	_tmp3_ = selected_leaf;
	if (_tmp3_ != NULL) {
		CaribouIScannableItem* _tmp4_ = NULL;
		CaribouIScannableItem* _tmp5_ = NULL;
		CaribouIScannableItem* _tmp6_ = NULL;
		CaribouIScannableItem* _tmp7_ = NULL;
		_tmp4_ = selected_leaf;
		_vala_assert (G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, CARIBOU_TYPE_ISCANNABLE_GROUP), "selected_leaf is IScannableGroup");
		_tmp5_ = selected_leaf;
		_tmp6_ = caribou_iscannable_group_child_select (G_TYPE_CHECK_INSTANCE_CAST (_tmp5_, CARIBOU_TYPE_ISCANNABLE_GROUP, CaribouIScannableGroup));
		_tmp7_ = _tmp6_;
		caribou_scannable_group_add_to_selected_path (self, _tmp7_);
		_g_object_unref0 (_tmp7_);
	} else {
		CaribouIScannableItem* _tmp8_ = NULL;
		_tmp8_ = step_child;
		if (_tmp8_ != NULL) {
			CaribouIScannableItem* _tmp9_ = NULL;
			CaribouIScannableItem* _tmp10_ = NULL;
			_tmp9_ = step_child;
			caribou_iscannable_item_set_scan_selected (_tmp9_, TRUE);
			_tmp10_ = step_child;
			caribou_scannable_group_add_to_selected_path (self, _tmp10_);
			caribou_scannable_group_set_scan_child_index (self, -1);
			{
				CaribouIScannableItem* child = NULL;
				CaribouIScannableItem* _tmp11_ = NULL;
				CaribouIScannableItem* _tmp12_ = NULL;
				_tmp11_ = step_child;
				_tmp12_ = caribou_scannable_group_get_single_child (self, _tmp11_);
				child = _tmp12_;
				{
					gboolean _tmp13_ = FALSE;
					_tmp13_ = TRUE;
					while (TRUE) {
						gboolean _tmp14_ = FALSE;
						CaribouIScannableItem* _tmp17_ = NULL;
						CaribouIScannableItem* _tmp18_ = NULL;
						CaribouIScannableItem* _tmp19_ = NULL;
						_tmp14_ = _tmp13_;
						if (!_tmp14_) {
							CaribouIScannableItem* _tmp15_ = NULL;
							CaribouIScannableItem* _tmp16_ = NULL;
							_tmp15_ = child;
							_tmp16_ = caribou_scannable_group_get_single_child (self, _tmp15_);
							_g_object_unref0 (child);
							child = _tmp16_;
						}
						_tmp13_ = FALSE;
						_tmp17_ = child;
						if (!(_tmp17_ != NULL)) {
							break;
						}
						_tmp18_ = child;
						caribou_iscannable_item_set_scan_selected (_tmp18_, TRUE);
						_tmp19_ = child;
						caribou_scannable_group_add_to_selected_path (self, _tmp19_);
					}
				}
				_g_object_unref0 (child);
			}
		}
	}
	_tmp20_ = self->priv->_selected_path;
	_tmp21_ = gee_deque_peek_tail ((GeeDeque*) _tmp20_);
	result = (CaribouIScannableItem*) _tmp21_;
	_g_object_unref0 (selected_leaf);
	_g_object_unref0 (step_child);
	return result;
}
