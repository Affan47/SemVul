fc_lport_recv_rnid_req(struct fc_lport *lport,
				   struct fc_frame *in_fp)
{
	struct fc_frame *fp;
	struct fc_els_rnid *req;
	struct {
		struct fc_els_rnid_resp rnid;
		struct fc_els_rnid_cid cid;
		struct fc_els_rnid_gen gen;
	} *rp;
	struct fc_seq_els_data rjt_data;
	u8 fmt;
	size_t len;

	FC_LPORT_DBG(lport, "Received RNID request while in state %s\n",
		     fc_lport_state(lport));

	req = fc_frame_payload_get(in_fp, sizeof(*req));
	if (!req) {
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		lport->tt.seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
	} else {
		fmt = req->rnid_fmt;
		len = sizeof(*rp);
		if (fmt != ELS_RNIDF_GEN ||
		    ntohl(lport->rnid_gen.rnid_atype) == 0) {
			fmt = ELS_RNIDF_NONE;
			len -= sizeof(rp->gen);
		}
		fp = fc_frame_alloc(lport, len);
		if (fp) {
			rp = fc_frame_payload_get(fp, len);
			memset(rp, 0, len);
			rp->rnid.rnid_cmd = ELS_LS_ACC;
			rp->rnid.rnid_fmt = fmt;
			rp->rnid.rnid_cid_len = sizeof(rp->cid);
			rp->cid.rnid_wwpn = htonll(lport->wwpn);
			rp->cid.rnid_wwnn = htonll(lport->wwnn);
			if (fmt == ELS_RNIDF_GEN) {
				rp->rnid.rnid_sid_len = sizeof(rp->gen);
				memcpy(&rp->gen, &lport->rnid_gen,
				       sizeof(rp->gen));
			}
			fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
			lport->tt.frame_send(lport, fp);
		}
	}
	fc_frame_free(in_fp);
}
