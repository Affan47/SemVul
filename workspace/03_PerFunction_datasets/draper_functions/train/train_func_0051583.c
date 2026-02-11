ldns_rr_list2str_fmt(const ldns_output_format *fmt, const ldns_rr_list *list)
{
	char *result = NULL;
	ldns_buffer *tmp_buffer = ldns_buffer_new(LDNS_MAX_PACKETLEN);

	if (!tmp_buffer) {
		return NULL;
	}
	if (list) {
		if (ldns_rr_list2buffer_str_fmt(
				   tmp_buffer, fmt, list)
			       	== LDNS_STATUS_OK) {
		}
	} else {
		if (fmt == NULL) {
			fmt = ldns_output_format_default;
		}
		if (fmt->flags & LDNS_COMMENT_NULLS) {
			ldns_buffer_printf(tmp_buffer, "; (null)\n");
		}
	}


	result = ldns_buffer_export2str(tmp_buffer);
	ldns_buffer_free(tmp_buffer);
	return result;
}
