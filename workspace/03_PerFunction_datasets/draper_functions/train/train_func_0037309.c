summary_header_load (CamelStoreSummary *s,
                     FILE *in)
{
	CamelNNTPStoreSummary *is = (CamelNNTPStoreSummary *) s;
	gint32 version, nil;

	if (CAMEL_STORE_SUMMARY_CLASS (camel_nntp_store_summary_parent_class)->summary_header_load ((CamelStoreSummary *) s, in) == -1
	    || camel_file_util_decode_fixed_int32 (in, &version) == -1)
		return -1;

	is->version = version;

	if (version < CAMEL_NNTP_STORE_SUMMARY_VERSION_0) {
		g_warning ("Store summary header version too low");
		return -1;
	}

	if (fread (is->last_newslist, 1, NNTP_DATE_SIZE, in) < NNTP_DATE_SIZE)
		return -1;

	return camel_file_util_decode_fixed_int32 (in, &nil);
}
