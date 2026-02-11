mbfl_convert_filter_reset(mbfl_convert_filter *filter,
	    enum mbfl_no_encoding from, enum mbfl_no_encoding to)
{
	const struct mbfl_convert_vtbl *vtbl;


	(*filter->filter_dtor)(filter);

	vtbl = mbfl_convert_filter_get_vtbl(from, to);

	if (vtbl == NULL) {
		vtbl = &vtbl_pass;
	}

	mbfl_convert_filter_common_init(filter, from, to, vtbl,
			filter->output_function, filter->flush_function, filter->data);
}
