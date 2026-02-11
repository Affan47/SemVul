clocks_geo_info_finalize (GObject* obj) {
	ClocksGeoInfo * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, CLOCKS_GEO_TYPE_INFO, ClocksGeoInfo);
	_g_object_unref0 (self->priv->_geo_location);
	_gweather_location_unref0 (self->priv->found_location);
	_g_free0 (self->priv->country_code);
	_g_object_unref0 (self->priv->manager);
	_g_object_unref0 (self->priv->client);
	G_OBJECT_CLASS (clocks_geo_info_parent_class)->finalize (obj);
}
