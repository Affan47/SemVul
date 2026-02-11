isl_schedule_band_member_set_coincident(
	__isl_take isl_schedule_band *band, int pos, int coincident)
{
	if (!band)
		return NULL;
	if (isl_schedule_band_member_get_coincident(band, pos) == coincident)
		return band;
	band = isl_schedule_band_cow(band);
	if (!band)
		return NULL;

	if (pos < 0 || pos >= band->n)
		isl_die(isl_schedule_band_get_ctx(band), isl_error_invalid,
			"invalid member position",
			isl_schedule_band_free(band));

	band->coincident[pos] = coincident;

	return band;
}
