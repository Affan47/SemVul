drm_dp_sideband_parse_remote_dpcd_read(struct drm_dp_sideband_msg_rx *raw,
						   struct drm_dp_sideband_msg_reply_body *repmsg)
{
	int idx = 1;
	repmsg->u.remote_dpcd_read_ack.port_number = raw->msg[idx] & 0xf;
	idx++;
	if (idx > raw->curlen)
		goto fail_len;
	repmsg->u.remote_dpcd_read_ack.num_bytes = raw->msg[idx];
	if (idx > raw->curlen)
		goto fail_len;

	memcpy(repmsg->u.remote_dpcd_read_ack.bytes, &raw->msg[idx], repmsg->u.remote_dpcd_read_ack.num_bytes);
	return true;
fail_len:
	DRM_DEBUG_KMS("link address reply parse length fail %d %d\n", idx, raw->curlen);
	return false;
}
