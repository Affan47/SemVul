sdp_attr_add_new_with_length(sdp_record_t *rec,
	uint16_t attr, uint8_t dtd, const void *value, uint32_t len)
{
	sdp_data_t *d;

	d = sdp_data_alloc_with_length(dtd, value, len);
	if (!d)
		return -1;

	sdp_attr_replace(rec, attr, d);

	return 0;
}
