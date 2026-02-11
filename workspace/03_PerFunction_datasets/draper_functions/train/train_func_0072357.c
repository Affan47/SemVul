rec_get_nth_field_offs_old(

	const rec_t*	rec,
	ulint		n,
	ulint*		len)

{
	ulint	os;
	ulint	next_os;

	ut_ad(len);
	ut_a(rec);
	ut_a(n < rec_get_n_fields_old(rec));

	if (rec_get_1byte_offs_flag(rec)) {
		os = rec_1_get_field_start_offs(rec, n);

		next_os = rec_1_get_field_end_info(rec, n);

		if (next_os & REC_1BYTE_SQL_NULL_MASK) {
			*len = UNIV_SQL_NULL;

			return(os);
		}

		next_os = next_os & ~REC_1BYTE_SQL_NULL_MASK;
	} else {
		os = rec_2_get_field_start_offs(rec, n);

		next_os = rec_2_get_field_end_info(rec, n);

		if (next_os & REC_2BYTE_SQL_NULL_MASK) {
			*len = UNIV_SQL_NULL;

			return(os);
		}

		next_os = next_os & ~(REC_2BYTE_SQL_NULL_MASK
				      | REC_2BYTE_EXTERN_MASK);
	}

	*len = next_os - os;

	ut_ad(*len < UNIV_PAGE_SIZE);

	return(os);
}
