compute_gain (xmms_xform_t *xform, xmms_replaygain_data_t *data)
{
	gfloat s, p;
	const gchar *key_s, *key_p, *tmp;

	if (data->mode == XMMS_REPLAYGAIN_MODE_TRACK) {
		key_s = XMMS_MEDIALIB_ENTRY_PROPERTY_GAIN_TRACK;
		key_p = XMMS_MEDIALIB_ENTRY_PROPERTY_PEAK_TRACK;
	} else {
		key_s = XMMS_MEDIALIB_ENTRY_PROPERTY_GAIN_ALBUM;
		key_p = XMMS_MEDIALIB_ENTRY_PROPERTY_PEAK_ALBUM;
	}


	if (xmms_xform_metadata_get_str (xform, key_s, &tmp)) {
		s = atof (tmp);
	} else {
		s = 1.0;
	}

	if (xmms_xform_metadata_get_str (xform, key_p, &tmp)) {
		p = atof (tmp);
	} else {
		p = 1.0;
	}

	s *= data->preamp;

	if (data->use_anticlip && s * p > 1.0) {
		s = 1.0 / p;
	}

	data->gain = MIN (s, 15.0);


	data->has_replaygain = (fabs (data->gain - 1.0) > 0.001);
}
