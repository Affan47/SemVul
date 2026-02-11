isl_band_free(__isl_take isl_band *band)
{
	if (!band)
		return NULL;

	if (--band->ref > 0) {
		isl_schedule_free(band->schedule);
		return NULL;
	}

	isl_union_pw_multi_aff_free(band->pma);
	isl_band_list_free(band->children);
	free(band->coincident);
	free(band);

	return NULL;
}
