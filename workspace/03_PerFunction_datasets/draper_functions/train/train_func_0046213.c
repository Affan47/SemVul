fc_rport_recv_els_req(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_rport_priv *rdata;
	struct fc_seq_els_data els_data;

	mutex_lock(&lport->disc.disc_mutex);
	rdata = lport->tt.rport_lookup(lport, fc_frame_sid(fp));
	if (!rdata) {
		mutex_unlock(&lport->disc.disc_mutex);
		goto reject;
	}
	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&lport->disc.disc_mutex);

	switch (rdata->rp_state) {
	case RPORT_ST_PRLI:
	case RPORT_ST_RTV:
	case RPORT_ST_READY:
	case RPORT_ST_ADISC:
		break;
	default:
		mutex_unlock(&rdata->rp_mutex);
		goto reject;
	}

	switch (fc_frame_payload_op(fp)) {
	case ELS_PRLI:
		fc_rport_recv_prli_req(rdata, fp);
		break;
	case ELS_PRLO:
		fc_rport_recv_prlo_req(rdata, fp);
		break;
	case ELS_ADISC:
		fc_rport_recv_adisc_req(rdata, fp);
		break;
	case ELS_RRQ:
		lport->tt.seq_els_rsp_send(fp, ELS_RRQ, NULL);
		fc_frame_free(fp);
		break;
	case ELS_REC:
		lport->tt.seq_els_rsp_send(fp, ELS_REC, NULL);
		fc_frame_free(fp);
		break;
	case ELS_RLS:
		fc_rport_recv_rls_req(rdata, fp);
		break;
	default:
		fc_frame_free(fp);
		break;
	}

	mutex_unlock(&rdata->rp_mutex);
	return;

reject:
	els_data.reason = ELS_RJT_UNAB;
	els_data.explan = ELS_EXPL_PLOGI_REQD;
	lport->tt.seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_free(fp);
}
