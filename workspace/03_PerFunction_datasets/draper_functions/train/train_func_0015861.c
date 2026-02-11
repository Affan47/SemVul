clocks_world_main_panel_save (ClocksWorldMainPanel* self) {
	GVariantBuilder* builder = NULL;
	GVariantType* _tmp0_ = NULL;
	GVariantType* _tmp1_ = NULL;
	GVariantBuilder* _tmp2_ = NULL;
	GVariantBuilder* _tmp3_ = NULL;
	GList* _tmp4_ = NULL;
	GSettings* _tmp11_ = NULL;
	GVariantBuilder* _tmp12_ = NULL;
	GVariant* _tmp13_ = NULL;
	GVariant* _tmp14_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_variant_type_new ("aa{sv}");
	_tmp1_ = _tmp0_;
	_tmp2_ = g_variant_builder_new (_tmp1_);
	_tmp3_ = _tmp2_;
	_g_variant_type_free0 (_tmp1_);
	builder = _tmp3_;
	_tmp4_ = self->priv->locations;
	{
		GList* i_collection = NULL;
		GList* i_it = NULL;
		i_collection = _tmp4_;
		for (i_it = i_collection; i_it != NULL; i_it = i_it->next) {
			ClocksWorldItem* _tmp5_ = NULL;
			ClocksWorldItem* i = NULL;
			_tmp5_ = _g_object_ref0 ((ClocksWorldItem*) i_it->data);
			i = _tmp5_;
			{
				ClocksWorldItem* _tmp6_ = NULL;
				gboolean _tmp7_ = FALSE;
				gboolean _tmp8_ = FALSE;
				_tmp6_ = i;
				_tmp7_ = clocks_world_item_get_automatic (_tmp6_);
				_tmp8_ = _tmp7_;
				if (!_tmp8_) {
					ClocksWorldItem* _tmp9_ = NULL;
					GVariantBuilder* _tmp10_ = NULL;
					_tmp9_ = i;
					_tmp10_ = builder;
					clocks_world_item_serialize (_tmp9_, _tmp10_);
				}
				_g_object_unref0 (i);
			}
		}
	}
	_tmp11_ = self->priv->settings;
	_tmp12_ = builder;
	_tmp13_ = g_variant_builder_end (_tmp12_);
	g_variant_ref_sink (_tmp13_);
	_tmp14_ = _tmp13_;
	g_settings_set_value (_tmp11_, "world-clocks", _tmp14_);
	_g_variant_unref0 (_tmp14_);
	_g_variant_builder_unref0 (builder);
}
