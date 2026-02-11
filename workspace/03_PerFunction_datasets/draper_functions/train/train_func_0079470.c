clocks_alarm_main_panel_load (ClocksAlarmMainPanel* self) {
	g_return_if_fail (self != NULL);
	{
		GVariantIter* _a_it = NULL;
		GSettings* _tmp0_ = NULL;
		GVariant* _tmp1_ = NULL;
		GVariant* _tmp2_ = NULL;
		GVariantIter* _tmp3_ = NULL;
		GVariantIter* _tmp4_ = NULL;
		GVariant* a = NULL;
		_tmp0_ = self->priv->settings;
		_tmp1_ = g_settings_get_value (_tmp0_, "alarms");
		_tmp2_ = _tmp1_;
		_tmp3_ = g_variant_iter_new (_tmp2_);
		_tmp4_ = _tmp3_;
		_g_variant_unref0 (_tmp2_);
		_a_it = _tmp4_;
		while (TRUE) {
			GVariantIter* _tmp5_ = NULL;
			GVariant* _tmp6_ = NULL;
			GVariant* _tmp7_ = NULL;
			ClocksAlarmItem* alarm = NULL;
			GVariant* _tmp8_ = NULL;
			ClocksAlarmItem* _tmp9_ = NULL;
			ClocksAlarmItem* _tmp10_ = NULL;
			_tmp5_ = _a_it;
			_tmp6_ = g_variant_iter_next_value (_tmp5_);
			_g_variant_unref0 (a);
			a = _tmp6_;
			_tmp7_ = a;
			if (!(_tmp7_ != NULL)) {
				break;
			}
			_tmp8_ = a;
			_tmp9_ = clocks_alarm_item_deserialize (_tmp8_);
			alarm = _tmp9_;
			_tmp10_ = alarm;
			if (_tmp10_ != NULL) {
				ClocksAlarmItem* _tmp11_ = NULL;
				ClocksAlarmItem* _tmp12_ = NULL;
				ClocksContentView* _tmp13_ = NULL;
				ClocksAlarmItem* _tmp14_ = NULL;
				_tmp11_ = alarm;
				_tmp12_ = _g_object_ref0 (_tmp11_);
				self->priv->alarms = g_list_prepend (self->priv->alarms, _tmp12_);
				_tmp13_ = self->priv->content_view;
				_tmp14_ = alarm;
				clocks_content_view_add_item (_tmp13_, (ClocksContentItem*) _tmp14_);
			}
			_g_object_unref0 (alarm);
		}
		_g_variant_unref0 (a);
		_g_variant_iter_free0 (_a_it);
	}
	self->priv->alarms = g_list_reverse (self->priv->alarms);
}
