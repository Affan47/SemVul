cheese_effects_manager_add_effect (CheeseEffectsManager* self, const gchar* name, CheeseEffect* effect) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (effect != NULL);
	{
		CheeseEffect* _tmp0_ = NULL;
		const gchar* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		GstBin* _tmp3_ = NULL;
		GstBin* _tmp4_ = NULL;
		CheeseEffect* _tmp5_ = NULL;
		CheeseEffect* _tmp6_ = NULL;
		_tmp0_ = effect;
		_tmp1_ = cheese_effect_get_pipeline_desc (_tmp0_);
		_tmp2_ = _tmp1_;
		_tmp3_ = gst_parse_bin_from_description_full (_tmp2_, FALSE, NULL, GST_PARSE_FLAG_FATAL_ERRORS, &_inner_error_);
		g_object_ref_sink (_tmp3_);
		_tmp4_ = _tmp3_;
		_g_object_unref0 (_tmp4_);
		if (_inner_error_ != NULL) {
			goto __catch4_g_error;
		}
		_tmp5_ = effect;
		_tmp6_ = _g_object_ref0 (_tmp5_);
		self->effects = g_list_insert_sorted (self->effects, _tmp6_, _cheese_effects_manager_sort_value_gcompare_func);
	}
	goto __finally4;
	__catch4_g_error:
	{
		GError* err = NULL;
		CheeseEffect* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		GError* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp7_ = effect;
		_tmp8_ = cheese_effect_get_name (_tmp7_);
		_tmp9_ = _tmp8_;
		_tmp10_ = err;
		_tmp11_ = _tmp10_->message;
		g_debug ("cheese-effects-manager.vala:70: Effect '%s' did not parse correctly, s" \
"kipping: %s", _tmp9_, _tmp11_);
		_g_error_free0 (err);
	}
	__finally4:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
