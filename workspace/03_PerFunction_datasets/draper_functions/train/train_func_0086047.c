jdns_response_append_additional(jdns_response_t *r, const jdns_rr_t *rr)
{
	ARRAY_APPEND(jdns_rr_t, r->additionalRecords, r->additionalCount, jdns_rr_copy(rr));
}
