sdp_get_service_avail(const sdp_record_t *rec, uint8_t *svcAvail)
{
	get_basic_attr(SDP_ATTR_SERVICE_AVAILABILITY, svcAvail, uint8);
}
