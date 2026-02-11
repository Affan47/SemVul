__lambda10_ (AlmPrivacyWidget* self, const gchar* blacklist_id, ZeitgeistEvent* blacklist_template) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	g_return_if_fail (blacklist_id != NULL);
	g_return_if_fail (blacklist_template != NULL);
	_tmp0_ = blacklist_id;
	_tmp1_ = alm_file_type_blacklist_interpretation_prefix;
	_tmp2_ = g_str_has_prefix (_tmp0_, _tmp1_);
	if (_tmp2_) {
		gchar* inter = NULL;
		ZeitgeistEvent* _tmp3_ = NULL;
		ZeitgeistSubject* _tmp4_ = NULL;
		ZeitgeistSubject* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		gchar* _tmp9_ = NULL;
		GeeHashMap* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		gboolean _tmp12_ = FALSE;
		self->priv->file_type_fire_signal = FALSE;
		_tmp3_ = blacklist_template;
		_tmp4_ = zeitgeist_event_get_subject (_tmp3_, 0);
		_tmp5_ = _tmp4_;
		_tmp6_ = zeitgeist_subject_get_interpretation (_tmp5_);
		_tmp7_ = _tmp6_;
		_tmp8_ = g_strdup (_tmp7_);
		_tmp9_ = _tmp8_;
		_g_object_unref0 (_tmp5_);
		inter = _tmp9_;
		_tmp10_ = self->priv->checkboxes;
		_tmp11_ = inter;
		_tmp12_ = gee_abstract_map_has_key ((GeeAbstractMap*) _tmp10_, _tmp11_);
		if (_tmp12_) {
			GeeHashMap* _tmp13_ = NULL;
			const gchar* _tmp14_ = NULL;
			gpointer _tmp15_ = NULL;
			GtkCheckButton* _tmp16_ = NULL;
			_tmp13_ = self->priv->checkboxes;
			_tmp14_ = inter;
			_tmp15_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp13_, _tmp14_);
			_tmp16_ = (GtkCheckButton*) _tmp15_;
			gtk_toggle_button_set_active ((GtkToggleButton*) _tmp16_, FALSE);
			_g_object_unref0 (_tmp16_);
		}
		self->priv->file_type_fire_signal = TRUE;
		_g_free0 (inter);
	}
}
