fc_lport_recv_echo_req(struct fc_lport *lport,
				   struct fc_frame *in_fp)
{
	struct fc_frame *fp;
	unsigned int len;
	void *pp;
	void *dp;

	FC_LPORT_DBG(lport, "Received ECHO request while in state %s\n",
		     fc_lport_state(lport));

	len = fr_len(in_fp) - sizeof(struct fc_frame_header);
	pp = fc_frame_payload_get(in_fp, len);

	if (len < sizeof(__be32))
		len = sizeof(__be32);

	fp = fc_frame_alloc(lport, len);
	if (fp) {
		dp = fc_frame_payload_get(fp, len);
		memcpy(dp, pp, len);
		*((__be32 *)dp) = htonl(ELS_LS_ACC << 24);
		fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
		lport->tt.frame_send(lport, fp);
	}
	fc_frame_free(in_fp);
}
