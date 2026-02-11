increment_counter(struct isl_scan_callback *cb,
	__isl_take isl_vec *sample)
{
	struct isl_counter *cnt = (struct isl_counter *)cb;

	isl_int_add_ui(cnt->count, cnt->count, 1);

	isl_vec_free(sample);

	if (isl_int_is_zero(cnt->max) || isl_int_lt(cnt->count, cnt->max))
		return 0;
	return -1;
}
