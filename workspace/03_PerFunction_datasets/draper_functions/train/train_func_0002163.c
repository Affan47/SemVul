bfa_fcs_fabric_process_flogi(struct bfa_fcs_fabric_s *fabric,
			struct fchs_s *fchs, u16 len)
{
	struct fc_logi_s *flogi = (struct fc_logi_s *) (fchs + 1);
	struct bfa_fcs_lport_s *bport = &fabric->bport;

	bfa_trc(fabric->fcs, fchs->s_id);

	fabric->stats.flogi_rcvd++;


	if (flogi->csp.port_type) {


		bfa_trc(fabric->fcs, flogi->port_name);
		fabric->stats.flogi_rejected++;
		return;
	}

	fabric->bb_credit = be16_to_cpu(flogi->csp.bbcred);
	bport->port_topo.pn2n.rem_port_wwn = flogi->port_name;
	bport->port_topo.pn2n.reply_oxid = fchs->ox_id;


	bfa_fcs_fabric_send_flogi_acc(fabric);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_NO_FABRIC);
}
