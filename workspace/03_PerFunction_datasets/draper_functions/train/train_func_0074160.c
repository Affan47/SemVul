fc_rport_enter_plogi(struct fc_rport_priv *rdata)
{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;

	if (!fc_rport_compatible_roles(lport, rdata)) {
		FC_RPORT_DBG(rdata, "PLOGI suppressed for incompatible role\n");
		fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
		return;
	}

	FC_RPORT_DBG(rdata, "Port entered PLOGI state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_PLOGI);

	rdata->maxframe_size = FC_MIN_MAX_PAYLOAD;
	fp = fc_frame_alloc(lport, sizeof(struct fc_els_flogi));
	if (!fp) {
		FC_RPORT_DBG(rdata, "%s frame alloc failed\n", __func__);
		fc_rport_error_retry(rdata, fp);
		return;
	}
	rdata->e_d_tov = lport->e_d_tov;

	if (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_PLOGI,
				  fc_rport_plogi_resp, rdata,
				  2 * lport->r_a_tov))
		fc_rport_error_retry(rdata, NULL);
	else
		kref_get(&rdata->kref);
}
