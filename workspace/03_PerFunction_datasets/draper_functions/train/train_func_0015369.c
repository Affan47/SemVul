sdp_get_int_attr(const sdp_record_t *rec, uint16_t attrid, int *value)
{
	sdp_data_t *sdpdata = sdp_data_get(rec, attrid);

	if (sdpdata)

		if (sdpdata->dtd == SDP_BOOL || sdpdata->dtd == SDP_UINT8 ||
		sdpdata->dtd == SDP_UINT16 || sdpdata->dtd == SDP_UINT32 ||
		sdpdata->dtd == SDP_INT8 || sdpdata->dtd == SDP_INT16 ||
		sdpdata->dtd == SDP_INT32) {
			*value = sdpdata->val.uint32;
			return 0;
		}
	errno = EINVAL;
	return -1;
}
