ldns_rr_list2buffer_str_fmt(ldns_buffer *output,
		const ldns_output_format *fmt, const ldns_rr_list *list)
{
	uint16_t i;

	for(i = 0; i < ldns_rr_list_rr_count(list); i++) {
		(void) ldns_rr2buffer_str_fmt(output, fmt,
				ldns_rr_list_rr(list, i));
	}
	return ldns_buffer_status(output);
}
