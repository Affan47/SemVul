qla2x00_mark_device_lost(scsi_qla_host_t *vha, fc_port_t *fcport,
    int do_login, int defer)
{
	if (IS_QLAFX00(vha->hw)) {
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport, defer);
		return;
	}

	if (atomic_read(&fcport->state) == FCS_ONLINE &&
	    vha->vp_idx == fcport->vha->vp_idx) {
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport, defer);
	}


	if (atomic_read(&fcport->state) != FCS_DEVICE_DEAD)
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);

	if (!do_login)
		return;

	set_bit(RELOGIN_NEEDED, &vha->dpc_flags);

	if (fcport->login_retry == 0) {
		fcport->login_retry = vha->hw->login_retry_count;

		ql_dbg(ql_dbg_disc, vha, 0x2067,
		    "Port login retry %8phN, id = 0x%04x retry cnt=%d.\n",
		    fcport->port_name, fcport->loop_id, fcport->login_retry);
	}
}
