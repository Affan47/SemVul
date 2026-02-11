abraca_transform_bitrate (xmmsv_t* val, gchar** repr) {
	gchar* _vala_repr = NULL;
	gboolean result = FALSE;
	gint bitrate = 0;
	xmmsv_t* _tmp0_;
	gint _tmp1_ = 0;
	gboolean _tmp2_ = FALSE;
	gint _tmp3_;
	gchar* _tmp4_ = NULL;
	g_return_val_if_fail (val != NULL, FALSE);
	_tmp0_ = val;
	_tmp2_ = xmmsv_get_int (_tmp0_, &_tmp1_);
	bitrate = _tmp1_;
	if (!_tmp2_) {
		result = FALSE;
		if (repr) {
			*repr = _vala_repr;
		} else {
			_g_free0 (_vala_repr);
		}
		return result;
	}
	_tmp3_ = bitrate;
	_tmp4_ = g_strdup_printf ("%.1f kbps", _tmp3_ / 1000.0);
	_g_free0 (_vala_repr);
	_vala_repr = _tmp4_;
	result = TRUE;
	if (repr) {
		*repr = _vala_repr;
	} else {
		_g_free0 (_vala_repr);
	}
	return result;
}
