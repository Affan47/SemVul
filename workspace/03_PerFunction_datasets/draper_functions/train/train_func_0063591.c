pnm_putsint(jas_stream_t *out, int wordsize, int_fast32_t *val)
{
	uint_fast32_t tmpval;
	tmpval = (*val < 0) ?
	  ((~(JAS_CAST(uint_fast32_t, -(*val)) + 1)) & PNM_ONES(wordsize)) :
	  JAS_CAST(uint_fast32_t, (*val));
	return pnm_putuint(out, wordsize, &tmpval);
}
