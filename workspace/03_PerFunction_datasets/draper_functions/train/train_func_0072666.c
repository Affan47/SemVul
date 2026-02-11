summary_header_save (CamelStoreSummary *s,
                     FILE *out)
{
	CamelNNTPStoreSummary *is = (CamelNNTPStoreSummary *) s;


	if (CAMEL_STORE_SUMMARY_CLASS (camel_nntp_store_summary_parent_class)->summary_header_save ((CamelStoreSummary *) s, out) == -1
	    || camel_file_util_encode_fixed_int32 (out, CAMEL_NNTP_STORE_SUMMARY_VERSION) == -1
	    || fwrite (is->last_newslist, 1, NNTP_DATE_SIZE, out) < NNTP_DATE_SIZE
	    || camel_file_util_encode_fixed_int32 (out, 0) == -1)
		return -1;

	return 0;
}
