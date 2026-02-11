abraca_medialib_info_dialog_on_rating_entry_changed (AbracaRatingEntry* entry, AbracaMedialibInfoDialog* self) {
	AbracaRatingEntry* _tmp0_;
	gint _tmp1_;
	gint _tmp2_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (entry != NULL);
	_tmp0_ = entry;
	_tmp1_ = abraca_rating_entry_get_rating (_tmp0_);
	_tmp2_ = _tmp1_;
	if (_tmp2_ <= 0) {
		AbracaClient* _tmp3_;
		xmmsc_connection_t* _tmp4_;
		xmmsc_connection_t* _tmp5_;
		GList* _tmp6_;
		gconstpointer _tmp7_;
		xmmsc_result_t* _tmp8_ = NULL;
		xmmsc_result_t* _tmp9_;
		_tmp3_ = self->priv->client;
		_tmp4_ = abraca_client_get_xmms (_tmp3_);
		_tmp5_ = _tmp4_;
		_tmp6_ = self->priv->current;
		_tmp7_ = _tmp6_->data;
		_tmp8_ = xmmsc_medialib_entry_property_remove_with_source (_tmp5_, GPOINTER_TO_UINT (_tmp7_), "client/generic", "rating");
		_tmp9_ = _tmp8_;
		xmmsc_result_notifier_set (_tmp9_, _abraca_medialib_info_dialog_on_value_wrote_xmmsc_result_notifier_t, self);
		_xmmsc_result_unref0 (_tmp9_);
	} else {
		AbracaClient* _tmp10_;
		xmmsc_connection_t* _tmp11_;
		xmmsc_connection_t* _tmp12_;
		GList* _tmp13_;
		gconstpointer _tmp14_;
		AbracaRatingEntry* _tmp15_;
		gint _tmp16_;
		gint _tmp17_;
		xmmsc_result_t* _tmp18_ = NULL;
		xmmsc_result_t* _tmp19_;
		_tmp10_ = self->priv->client;
		_tmp11_ = abraca_client_get_xmms (_tmp10_);
		_tmp12_ = _tmp11_;
		_tmp13_ = self->priv->current;
		_tmp14_ = _tmp13_->data;
		_tmp15_ = entry;
		_tmp16_ = abraca_rating_entry_get_rating (_tmp15_);
		_tmp17_ = _tmp16_;
		_tmp18_ = xmmsc_medialib_entry_property_set_int_with_source (_tmp12_, GPOINTER_TO_UINT (_tmp14_), "client/generic", "rating", _tmp17_);
		_tmp19_ = _tmp18_;
		xmmsc_result_notifier_set (_tmp19_, _abraca_medialib_info_dialog_on_value_wrote_xmmsc_result_notifier_t, self);
		_xmmsc_result_unref0 (_tmp19_);
	}
}
