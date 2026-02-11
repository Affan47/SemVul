opt_garman_kohlhagen1 (OptionSide side,
		       gnm_float s, gnm_float x, gnm_float t,
		       gnm_float r, gnm_float rf, gnm_float v)
{
	gnm_float d1 = (gnm_log (s / x) + (r - rf + (v * v) / 2.0) * t) / (v * gnm_sqrt (t));
	gnm_float d2 = d1 - v * gnm_sqrt (t);
	switch (side) {
	case OS_Call:
		return s * gnm_exp (-rf * t) * ncdf (d1) - x * gnm_exp (-r * t) * ncdf (d2);
	case OS_Put:
		return x * gnm_exp (-r * t) * ncdf (-d2) - s * gnm_exp (-rf * t) * ncdf (-d1);
	default:
		return gnm_nan;
	}
}
