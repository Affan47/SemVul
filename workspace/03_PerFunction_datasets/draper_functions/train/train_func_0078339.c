dvb_satellite_channel_real_setup_dvb_source (DVBChannel* base, GstElement* source) {
	DVBSatelliteChannel * self;
	GstElement* _tmp0_ = NULL;
	guint _tmp1_ = 0U;
	guint _tmp2_ = 0U;
	GstElement* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	GstElement* _tmp5_ = NULL;
	guint _tmp6_ = 0U;
	GstElement* _tmp7_ = NULL;
	gint _tmp8_ = 0;
	self = (DVBSatelliteChannel*) base;
	g_return_if_fail (source != NULL);
	_tmp0_ = source;
	_tmp1_ = dvb_channel_get_Frequency ((DVBChannel*) self);
	_tmp2_ = _tmp1_;
	g_object_set ((GObject*) _tmp0_, "frequency", _tmp2_, NULL);
	_tmp3_ = source;
	_tmp4_ = self->priv->_Polarization;
	g_object_set ((GObject*) _tmp3_, "polarity", _tmp4_, NULL);
	_tmp5_ = source;
	_tmp6_ = self->priv->_SymbolRate;
	g_object_set ((GObject*) _tmp5_, "symbol-rate", _tmp6_, NULL);
	_tmp7_ = source;
	_tmp8_ = self->priv->_DiseqcSource;
	g_object_set ((GObject*) _tmp7_, "diseqc-source", _tmp8_, NULL);
}
