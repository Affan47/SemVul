folks_abstract_field_details_get_parameter_values (FolksAbstractFieldDetails* self, const gchar* parameter_name) {
	GeeCollection* result = NULL;
	GeeMultiMap* _tmp0_ = NULL;
	GeeMultiMap* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	GeeMultiMap* _tmp4_ = NULL;
	GeeMultiMap* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	GeeCollection* _tmp7_ = NULL;
	GeeCollection* _tmp8_ = NULL;
	GeeCollection* _tmp9_ = NULL;
	GeeCollection* _tmp10_ = NULL;
	GeeCollection* _tmp11_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (parameter_name != NULL, NULL);
	_tmp0_ = folks_abstract_field_details_get_parameters (self);
	_tmp1_ = _tmp0_;
	_tmp2_ = parameter_name;
	_tmp3_ = gee_multi_map_contains (_tmp1_, _tmp2_);
	if (_tmp3_ == FALSE) {
		result = NULL;
		return result;
	}
	_tmp4_ = folks_abstract_field_details_get_parameters (self);
	_tmp5_ = _tmp4_;
	_tmp6_ = parameter_name;
	_tmp7_ = gee_multi_map_get (_tmp5_, _tmp6_);
	_tmp8_ = _tmp7_;
	_tmp9_ = gee_collection_get_read_only_view (_tmp8_);
	_tmp10_ = _tmp9_;
	_tmp11_ = _tmp10_;
	_g_object_unref0 (_tmp8_);
	result = _tmp11_;
	return result;
}
