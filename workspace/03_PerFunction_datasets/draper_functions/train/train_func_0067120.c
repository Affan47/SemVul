_tpf_persona_store_contact_info_set_to_list (FolksSmallSet* info_set) {
	GList* result = NULL;
	GList* info_list = NULL;
	g_return_val_if_fail (info_set != NULL, NULL);
	info_list = NULL;
	{
		FolksSmallSet* _info_field_list = NULL;
		FolksSmallSet* _tmp0_ = NULL;
		FolksSmallSet* _tmp1_ = NULL;
		gint _info_field_size = 0;
		FolksSmallSet* _tmp2_ = NULL;
		gint _tmp3_ = 0;
		gint _tmp4_ = 0;
		gint _info_field_index = 0;
		_tmp0_ = info_set;
		_tmp1_ = _g_object_ref0 (_tmp0_);
		_info_field_list = _tmp1_;
		_tmp2_ = _info_field_list;
		_tmp3_ = gee_collection_get_size ((GeeCollection*) _tmp2_);
		_tmp4_ = _tmp3_;
		_info_field_size = _tmp4_;
		_info_field_index = -1;
		while (TRUE) {
			gint _tmp5_ = 0;
			gint _tmp6_ = 0;
			gint _tmp7_ = 0;
			TpContactInfoField* info_field = NULL;
			FolksSmallSet* _tmp8_ = NULL;
			gint _tmp9_ = 0;
			gconstpointer _tmp10_ = NULL;
			TpContactInfoField* _tmp11_ = NULL;
			TpContactInfoField* _tmp12_ = NULL;
			const gchar* _tmp13_ = NULL;
			TpContactInfoField* _tmp14_ = NULL;
			gchar** _tmp15_ = NULL;
			gint _tmp15__length1 = 0;
			TpContactInfoField* _tmp16_ = NULL;
			gchar** _tmp17_ = NULL;
			gint _tmp17__length1 = 0;
			TpContactInfoField* _tmp18_ = NULL;
			_tmp5_ = _info_field_index;
			_info_field_index = _tmp5_ + 1;
			_tmp6_ = _info_field_index;
			_tmp7_ = _info_field_size;
			if (!(_tmp6_ < _tmp7_)) {
				break;
			}
			_tmp8_ = _info_field_list;
			_tmp9_ = _info_field_index;
			_tmp10_ = folks_small_set_get (_tmp8_, _tmp9_);
			_tmp11_ = __vala_TpContactInfoField_copy0 ((TpContactInfoField*) _tmp10_);
			info_field = _tmp11_;
			_tmp12_ = info_field;
			_tmp13_ = _tmp12_->field_name;
			_tmp14_ = info_field;
			_tmp15_ = _tmp14_->parameters;
			_tmp15__length1 = _vala_array_length (_tmp14_->parameters);
			_tmp16_ = info_field;
			_tmp17_ = _tmp16_->field_value;
			_tmp17__length1 = _vala_array_length (_tmp16_->field_value);
			_tmp18_ = tp_contact_info_field_new (_tmp13_, _tmp15_, _tmp17_);
			info_list = g_list_prepend (info_list, _tmp18_);
			__vala_TpContactInfoField_free0 (info_field);
		}
		_g_object_unref0 (_info_field_list);
	}
	info_list = g_list_reverse (info_list);
	result = info_list;
	return result;
}
