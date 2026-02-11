caribou_scannable_group_real_set_scan_grouping (CaribouIScannableGroup* base, CaribouScanGrouping value) {
	CaribouScannableGroup* self;
	CaribouScanGrouping _tmp0_ = 0;
	gint _tmp1_ = 0;
	CaribouIScannableItem** _tmp2_ = NULL;
	self = (CaribouScannableGroup*) base;
	_tmp0_ = value;
	self->priv->_scan_grouping = _tmp0_;
	_tmp2_ = caribou_scannable_group_get_scan_children (self, &_tmp1_);
	{
		CaribouIScannableItem** item_collection = NULL;
		gint item_collection_length1 = 0;
		gint _item_collection_size_ = 0;
		gint item_it = 0;
		item_collection = _tmp2_;
		item_collection_length1 = _tmp1_;
		for (item_it = 0; item_it < _tmp1_; item_it = item_it + 1) {
			CaribouIScannableItem* _tmp3_ = NULL;
			CaribouIScannableItem* item = NULL;
			_tmp3_ = _g_object_ref0 (item_collection[item_it]);
			item = _tmp3_;
			{
				CaribouIScannableItem* _tmp4_ = NULL;
				_tmp4_ = item;
				if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, CARIBOU_TYPE_ISCANNABLE_GROUP)) {
					CaribouIScannableItem* _tmp5_ = NULL;
					CaribouScanGrouping _tmp6_ = 0;
					_tmp5_ = item;
					_tmp6_ = value;
					caribou_iscannable_group_set_scan_grouping (G_TYPE_CHECK_INSTANCE_CAST (_tmp5_, CARIBOU_TYPE_ISCANNABLE_GROUP, CaribouIScannableGroup), _tmp6_);
				}
				_g_object_unref0 (item);
			}
		}
		item_collection = (_vala_array_free (item_collection, item_collection_length1, (GDestroyNotify) g_object_unref), NULL);
	}
	g_object_notify ((GObject *) self, "scan-grouping");
}
