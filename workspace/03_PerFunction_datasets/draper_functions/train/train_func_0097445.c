unity_tester_series_preview_renderer_on_change_selected_item_clicked (UnityTesterSeriesPreviewRenderer* self, GtkComboBox* combo) {
	gint index = 0;
	GtkComboBox* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	UnityProtocolSeriesPreview* series_preview = NULL;
	UnityProtocolPreview* _tmp4_ = NULL;
	UnityProtocolPreview* _tmp5_ = NULL;
	UnityProtocolSeriesPreview* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	UnityProtocolSeriesPreview* _tmp8_ = NULL;
	gint _tmp9_ = 0;
	gint _tmp10_ = 0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (combo != NULL);
	_tmp0_ = combo;
	_tmp1_ = gtk_combo_box_get_active_id (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = atoi (_tmp2_);
	index = _tmp3_;
	_tmp4_ = unity_tester_preview_renderer_get_preview ((UnityTesterPreviewRenderer*) self);
	_tmp5_ = _tmp4_;
	_tmp6_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp5_, UNITY_PROTOCOL_TYPE_SERIES_PREVIEW) ? ((UnityProtocolSeriesPreview*) _tmp5_) : NULL);
	series_preview = _tmp6_;
	_tmp7_ = index;
	_tmp8_ = series_preview;
	_tmp9_ = unity_protocol_series_preview_get_selected_item (_tmp8_);
	_tmp10_ = _tmp9_;
	if (_tmp7_ != _tmp10_) {
		const gchar* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		gint _tmp13_ = 0;
		_tmp11_ = unity_tester_preview_renderer_get_scope_uri ((UnityTesterPreviewRenderer*) self);
		_tmp12_ = _tmp11_;
		_tmp13_ = index;
		g_signal_emit_by_name (self, "change-selected-series-item-clicked", _tmp12_, _tmp13_);
	}
	_g_object_unref0 (series_preview);
}
