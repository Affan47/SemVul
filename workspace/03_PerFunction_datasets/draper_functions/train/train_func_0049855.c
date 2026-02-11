qlt_make_local_sess(struct scsi_qla_host *vha,
	uint8_t *s_id)
{
	struct qla_tgt_sess *sess = NULL;
	fc_port_t *fcport = NULL;
	int rc, global_resets;
	uint16_t loop_id = 0;

	mutex_lock(&vha->vha_tgt.tgt_mutex);

retry:
	global_resets =
	    atomic_read(&vha->vha_tgt.qla_tgt->tgt_global_resets_count);

	rc = qla24xx_get_loop_id(vha, s_id, &loop_id);
	if (rc != 0) {
		mutex_unlock(&vha->vha_tgt.tgt_mutex);

		if ((s_id[0] == 0xFF) &&
		    (s_id[1] == 0xFC)) {


			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf042,
			    "Unable to find initiator with S_ID %x:%x:%x",
			    s_id[0], s_id[1], s_id[2]);
		} else
			ql_log(ql_log_info, vha, 0xf071,
			    "qla_target(%d): Unable to find "
			    "initiator with S_ID %x:%x:%x",
			    vha->vp_idx, s_id[0], s_id[1],
			    s_id[2]);

		if (rc == -ENOENT) {
			qlt_port_logo_t logo;
			sid_to_portid(s_id, &logo.id);
			logo.cmd_count = 1;
			qlt_send_first_logo(vha, &logo);
		}

		return NULL;
	}

	fcport = qlt_get_port_database(vha, loop_id);
	if (!fcport) {
		mutex_unlock(&vha->vha_tgt.tgt_mutex);
		return NULL;
	}

	if (global_resets !=
	    atomic_read(&vha->vha_tgt.qla_tgt->tgt_global_resets_count)) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf043,
		    "qla_target(%d): global reset during session discovery "
		    "(counter was %d, new %d), retrying", vha->vp_idx,
		    global_resets,
		    atomic_read(&vha->vha_tgt.
			qla_tgt->tgt_global_resets_count));
		goto retry;
	}

	sess = qlt_create_sess(vha, fcport, true);

	mutex_unlock(&vha->vha_tgt.tgt_mutex);

	kfree(fcport);
	return sess;
}
