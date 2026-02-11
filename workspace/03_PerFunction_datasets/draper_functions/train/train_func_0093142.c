get_single_cache_key_from_value (GnmValue const *r, GnmEvalPos const *ep)
{
	GnmValue *key;
	GnmSheetRange sr;
	GnmRangeRef const *rr;
	Sheet *end_sheet;
	int h, w;
	const int min_size = 25;

	rr = value_get_rangeref (r);
	gnm_rangeref_normalize (rr, ep, &sr.sheet, &end_sheet, &sr.range);
	if (sr.sheet != end_sheet)
		return NULL;

	h = range_height (&sr.range);
	w = range_width (&sr.range);
	if (h < min_size && w < min_size && h * w < min_size)
		return NULL;

	key = value_new_cellrange_r (sr.sheet, &sr.range);

	return key;
}
