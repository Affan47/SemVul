clocks_world_item_construct (GType object_type, GWeatherLocation* location) {
	ClocksWorldItem * self = NULL;
	GWeatherLocation* _tmp0_ = NULL;
	GWeatherTimezone* weather_time_zone = NULL;
	GWeatherLocation* _tmp1_ = NULL;
	GWeatherTimezone* _tmp2_ = NULL;
	GWeatherTimezone* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	GTimeZone* _tmp5_ = NULL;
	g_return_val_if_fail (location != NULL, NULL);
	_tmp0_ = location;
	self = (ClocksWorldItem*) g_object_new (object_type, "location", _tmp0_, NULL);
	_tmp1_ = location;
	_tmp2_ = gweather_location_get_timezone (_tmp1_);
	_tmp3_ = _gweather_timezone_ref0 (_tmp2_);
	weather_time_zone = _tmp3_;
	_tmp4_ = gweather_timezone_get_tzid (weather_time_zone);
	_tmp5_ = g_time_zone_new (_tmp4_);
	_g_time_zone_unref0 (self->priv->time_zone);
	self->priv->time_zone = _tmp5_;
	clocks_world_item_tick (self);
	_gweather_timezone_unref0 (weather_time_zone);
	return self;
}
