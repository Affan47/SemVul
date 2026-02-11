gf_rtsp_register_interleave(GF_RTSPSession *sess, void *the_ch, u8 LowInterID, u8 HighInterID)
{
	GF_TCPChan *ptr;

	if (!sess) return GF_BAD_PARAM;

	gf_mx_p(sess->mx);

	ptr = GetTCPChannel(sess, LowInterID, HighInterID, 0);
	if (!ptr) {
		ptr = (GF_TCPChan *)gf_malloc(sizeof(GF_TCPChan));
		ptr->ch_ptr = the_ch;
		ptr->rtpID = LowInterID;
		ptr->rtcpID = HighInterID;
		gf_list_add(sess->TCPChannels, ptr);
	}
	gf_mx_v(sess->mx);
	return GF_OK;
}
