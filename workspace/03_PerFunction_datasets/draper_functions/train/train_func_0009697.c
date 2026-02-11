gf_rtsp_set_interleave_callback(GF_RTSPSession *sess,
						GF_Err (*SignalData)(GF_RTSPSession *sess, void *chan, char *buffer, u32 bufferSize, Bool IsRTCP)
				)
{
	if (!sess) return GF_BAD_PARAM;

	gf_mx_p(sess->mx);


	if (SignalData) sess->RTSP_SignalData = SignalData;


	if (sess->rtsp_pck_buf && sess->rtsp_pck_size != RTSP_PCK_SIZE) {
		sess->rtsp_pck_size = RTSP_PCK_SIZE;
		sess->rtsp_pck_buf = (char *)gf_realloc(sess->rtsp_pck_buf, sizeof(char)*sess->rtsp_pck_size);
	} else if (!sess->rtsp_pck_buf) {
		sess->rtsp_pck_size = RTSP_PCK_SIZE;
		sess->rtsp_pck_buf = (char *)gf_realloc(sess->rtsp_pck_buf, sizeof(char)*sess->rtsp_pck_size);
		sess->pck_start = 0;
	}
	gf_mx_v(sess->mx);
	return GF_OK;
}
