sdp_get_service_id(const sdp_record_t *rec, uuid_t *uuid)
{
	get_basic_attr(SDP_ATTR_SERVICE_ID, uuid, uuid);
}
