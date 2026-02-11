RP_cleanup(RTPClient *rtp)
{
	RTSPSession *sess;

	while (gf_list_count(rtp->channels)) {
		RTPStream *ch = (RTPStream *)gf_list_get(rtp->channels, 0);
		gf_list_rem(rtp->channels, 0);
		RP_DeleteStream(ch);
	}

	while ( (sess = (RTSPSession *)gf_list_last(rtp->sessions)) ) {
		gf_list_rem_last(rtp->sessions);
		RP_DelSession(sess);
	}

	if (rtp->session_desc) gf_odf_desc_del(rtp->session_desc);
	rtp->session_desc = NULL;

	if (rtp->sdp_temp) {
		gf_free(rtp->sdp_temp->remote_url);
		gf_free(rtp->sdp_temp);
	}
	rtp->sdp_temp = NULL;
}
