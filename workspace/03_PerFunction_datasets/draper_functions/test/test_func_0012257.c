sinc_set_converter (SRC_PRIVATE *psrc, int src_enum)
{	SINC_FILTER *filter, temp_filter ;
	int count ;


	if (SHIFT_BITS >= sizeof (increment_t) * 8 - 1)
		return SRC_ERR_SHIFT_BITS ;

	if (psrc->private_data != NULL)
	{	filter = (SINC_FILTER*) psrc->private_data ;
		if (filter->sinc_magic_marker != SINC_MAGIC_MARKER)
		{	g_free (psrc->private_data) ;
			psrc->private_data = NULL ;
			} ;
		} ;

	memset (&temp_filter, 0, sizeof (temp_filter)) ;

	temp_filter.sinc_magic_marker = SINC_MAGIC_MARKER ;
	temp_filter.channels = psrc->channels ;

	psrc->process = sinc_process ;
	psrc->reset = sinc_reset ;

	switch (src_enum)
	{
		case SRC_SINC_FASTEST :
				temp_filter.coeffs = fastest_coeffs ;
				temp_filter.coeff_half_len = (sizeof (fastest_coeffs) / sizeof (coeff_t)) - 1 ;
				temp_filter.index_inc = 128 ;
				temp_filter.has_diffs = SRC_FALSE ;
				temp_filter.coeff_len = sizeof (fastest_coeffs) / sizeof (coeff_t) ;
				break ;

		default :
				return SRC_ERR_BAD_CONVERTER ;
		} ;


	temp_filter.b_len = 1000 + 2 * lrint (ceil (temp_filter.coeff_len / (temp_filter.index_inc * 1.0) * SRC_MAX_RATIO)) ;
	temp_filter.b_len *= temp_filter.channels ;

	if ((filter = g_malloc0 (sizeof (SINC_FILTER) + sizeof (filter->buffer [0]) * (temp_filter.b_len + temp_filter.channels))) == NULL)
		return SRC_ERR_MALLOC_FAILED ;

	*filter = temp_filter ;
	memset (&temp_filter, 0xEE, sizeof (temp_filter)) ;

	psrc->private_data = filter ;

	sinc_reset (psrc) ;

	count = (filter->coeff_half_len * INT_TO_FP (1)) / FP_ONE ;

	if (abs (count - filter->coeff_half_len) >= 1)
		return SRC_ERR_FILTER_LEN ;

	return SRC_ERR_NO_ERROR ;
}
