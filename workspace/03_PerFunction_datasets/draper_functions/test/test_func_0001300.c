fc_lport_ms_resp(struct fc_seq *sp, struct fc_frame *fp,
			     void *lp_arg)
{
	struct fc_lport *lport = lp_arg;
	struct fc_frame_header *fh;
	struct fc_ct_hdr *ct;

	FC_LPORT_DBG(lport, "Received a ms %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		return;

	mutex_lock(&lport->lp_mutex);

	if (lport->state < LPORT_ST_RHBA || lport->state > LPORT_ST_DPRT) {
		FC_LPORT_DBG(lport, "Received a management server response, "
			     "but in state %s\n", fc_lport_state(lport));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_lport_error(lport, fp);
		goto err;
	}

	fh = fc_frame_header_get(fp);
	ct = fc_frame_payload_get(fp, sizeof(*ct));

	if (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_MGMT &&
	    ct->ct_fs_subtype == FC_FDMI_SUBTYPE) {
		FC_LPORT_DBG(lport, "Received a management server response, "
				    "reason=%d explain=%d\n",
				    ct->ct_reason,
				    ct->ct_explan);

		switch (lport->state) {
		case LPORT_ST_RHBA:
			if (ntohs(ct->ct_cmd) == FC_FS_ACC)
				fc_lport_enter_ms(lport, LPORT_ST_RPA);
			else
				fc_lport_enter_scr(lport);
			break;
		case LPORT_ST_RPA:
			fc_lport_enter_scr(lport);
			break;
		case LPORT_ST_DPRT:
			fc_lport_enter_ms(lport, LPORT_ST_RHBA);
			break;
		case LPORT_ST_DHBA:
			fc_lport_enter_ms(lport, LPORT_ST_DPRT);
			break;
		default:

			break;
		}
	} else {

		fc_lport_error(lport, fp);
	}
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&lport->lp_mutex);
}
