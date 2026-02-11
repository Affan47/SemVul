clocks_world_item_deserialize (GVariant* location_variant) {
	ClocksWorldItem* result = NULL;
	GWeatherLocation* location = NULL;
	GWeatherLocation* world = NULL;
	GWeatherLocation* _tmp0_ = NULL;
	GWeatherLocation* _tmp1_ = NULL;
	ClocksWorldItem* _tmp21_ = NULL;
	GWeatherLocation* _tmp22_ = NULL;
	g_return_val_if_fail (location_variant != NULL, NULL);
	location = NULL;
	_tmp0_ = gweather_location_get_world ();
	_tmp1_ = _gweather_location_ref0 (_tmp0_);
	world = _tmp1_;
	{
		GVariantIter* _v_it = NULL;
		GVariant* _tmp2_ = NULL;
		GVariantIter* _tmp3_ = NULL;
		GVariant* v = NULL;
		_tmp2_ = location_variant;
		_tmp3_ = g_variant_iter_new (_tmp2_);
		_v_it = _tmp3_;
		while (TRUE) {
			GVariantIter* _tmp4_ = NULL;
			GVariant* _tmp5_ = NULL;
			GVariant* _tmp6_ = NULL;
			gchar* key = NULL;
			GVariant* _tmp7_ = NULL;
			GVariant* _tmp8_ = NULL;
			GVariant* _tmp9_ = NULL;
			const gchar* _tmp10_ = NULL;
			gchar* _tmp11_ = NULL;
			gchar* _tmp12_ = NULL;
			const gchar* _tmp13_ = NULL;
			_tmp4_ = _v_it;
			_tmp5_ = g_variant_iter_next_value (_tmp4_);
			_g_variant_unref0 (v);
			v = _tmp5_;
			_tmp6_ = v;
			if (!(_tmp6_ != NULL)) {
				break;
			}
			_tmp7_ = v;
			_tmp8_ = g_variant_get_child_value (_tmp7_, (gsize) 0);
			_tmp9_ = _tmp8_;
			_tmp10_ = g_variant_get_string (_tmp9_, NULL);
			_tmp11_ = g_strdup (_tmp10_);
			_tmp12_ = _tmp11_;
			_g_variant_unref0 (_tmp9_);
			key = _tmp12_;
			_tmp13_ = key;
			if (g_strcmp0 (_tmp13_, "location") == 0) {
				GWeatherLocation* _tmp14_ = NULL;
				GVariant* _tmp15_ = NULL;
				GVariant* _tmp16_ = NULL;
				GVariant* _tmp17_ = NULL;
				GVariant* _tmp18_ = NULL;
				GVariant* _tmp19_ = NULL;
				GWeatherLocation* _tmp20_ = NULL;
				_tmp14_ = world;
				_tmp15_ = v;
				_tmp16_ = g_variant_get_child_value (_tmp15_, (gsize) 1);
				_tmp17_ = _tmp16_;
				_tmp18_ = g_variant_get_child_value (_tmp17_, (gsize) 0);
				_tmp19_ = _tmp18_;
				_tmp20_ = gweather_location_deserialize (_tmp14_, _tmp19_);
				_gweather_location_unref0 (location);
				location = _tmp20_;
				_g_variant_unref0 (_tmp19_);
				_g_variant_unref0 (_tmp17_);
			}
			_g_free0 (key);
		}
		_g_variant_unref0 (v);
		_g_variant_iter_free0 (_v_it);
	}
	_tmp22_ = location;
	if (_tmp22_ != NULL) {
		GWeatherLocation* _tmp23_ = NULL;
		ClocksWorldItem* _tmp24_ = NULL;
		_tmp23_ = location;
		_tmp24_ = clocks_world_item_new (_tmp23_);
		_g_object_unref0 (_tmp21_);
		_tmp21_ = _tmp24_;
	} else {
		_g_object_unref0 (_tmp21_);
		_tmp21_ = NULL;
	}
	result = _tmp21_;
	_gweather_location_unref0 (world);
	_gweather_location_unref0 (location);
	return result;
}
