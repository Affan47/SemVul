_osd_req_encode_common(struct osd_request *or,
	__be16 act, const struct osd_obj_id *obj, u64 offset, u64 len)
{
	if (osd_req_is_ver1(or))
		_osdv1_req_encode_common(or, act, obj, offset, len);
	else
		_osdv2_req_encode_common(or, act, obj, offset, len);
}
