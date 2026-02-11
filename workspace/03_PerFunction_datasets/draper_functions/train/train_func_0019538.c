dvb_cable_scanner_real_prepare (DVBScanner* base) {
	DVBCableScanner * self;
	GstElement* dvbsrc = NULL;
	GstElement* _tmp0_ = NULL;
	GstElement* _tmp1_ = NULL;
	gchar** keys = NULL;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar** _tmp4_ = NULL;
	gint keys_length1 = 0;
	gint _keys_size_ = 0;
	gchar** _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	GstElement* _tmp10_ = NULL;
	const GstStructure* _tmp11_ = NULL;
	const gchar* _tmp12_ = NULL;
	DVBDvbSrcModulation _tmp13_ = 0;
	GstElement* _tmp14_ = NULL;
	const GstStructure* _tmp15_ = NULL;
	const gchar* _tmp16_ = NULL;
	DVBDvbSrcCodeRate _tmp17_ = 0;
	self = (DVBCableScanner*) base;
	g_debug ("CableScanner.vala:87: Setting up pipeline for DVB-C scan");
	_tmp0_ = ((DVBScanner*) self)->pipeline;
	_tmp1_ = gst_bin_get_by_name (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, GST_TYPE_BIN, GstBin), "dvbsrc");
	dvbsrc = _tmp1_;
	_tmp2_ = g_strdup ("frequency");
	_tmp3_ = g_strdup ("symbol-rate");
	_tmp4_ = g_new0 (gchar*, 2 + 1);
	_tmp4_[0] = _tmp2_;
	_tmp4_[1] = _tmp3_;
	keys = _tmp4_;
	keys_length1 = 2;
	_keys_size_ = keys_length1;
	_tmp5_ = keys;
	_tmp5__length1 = keys_length1;
	{
		gchar** key_collection = NULL;
		gint key_collection_length1 = 0;
		gint _key_collection_size_ = 0;
		gint key_it = 0;
		key_collection = _tmp5_;
		key_collection_length1 = _tmp5__length1;
		for (key_it = 0; key_it < _tmp5__length1; key_it = key_it + 1) {
			gchar* _tmp6_ = NULL;
			gchar* key = NULL;
			_tmp6_ = g_strdup (key_collection[key_it]);
			key = _tmp6_;
			{
				GstElement* _tmp7_ = NULL;
				const GstStructure* _tmp8_ = NULL;
				const gchar* _tmp9_ = NULL;
				_tmp7_ = dvbsrc;
				_tmp8_ = ((DVBScanner*) self)->current_tuning_params;
				_tmp9_ = key;
				dvb_scanner_set_uint_property (_tmp7_, _tmp8_, _tmp9_);
				_g_free0 (key);
			}
		}
	}
	_tmp10_ = dvbsrc;
	_tmp11_ = ((DVBScanner*) self)->current_tuning_params;
	_tmp12_ = gst_structure_get_string (_tmp11_, "modulation");
	_tmp13_ = dvb_get_modulation_val (_tmp12_);
	g_object_set ((GObject*) _tmp10_, "modulation", _tmp13_, NULL);
	_tmp14_ = dvbsrc;
	_tmp15_ = ((DVBScanner*) self)->current_tuning_params;
	_tmp16_ = gst_structure_get_string (_tmp15_, "inner-fec");
	_tmp17_ = dvb_get_code_rate_val (_tmp16_);
	g_object_set ((GObject*) _tmp14_, "code-rate-hp", _tmp17_, NULL);
	keys = (_vala_array_free (keys, keys_length1, (GDestroyNotify) g_free), NULL);
	_gst_object_unref0 (dvbsrc);
}
