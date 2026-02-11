qlt_get_port_database(struct scsi_qla_host *vha,
	uint16_t loop_id)
{
	fc_port_t *fcport;
	int rc;

	fcport = kzalloc(sizeof(*fcport), GFP_KERNEL);
	if (!fcport) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06f,
		    "qla_target(%d): Allocation of tmp FC port failed",
		    vha->vp_idx);
		return NULL;
	}

	fcport->loop_id = loop_id;

	rc = qla2x00_get_port_database(vha, fcport, 0);
	if (rc != QLA_SUCCESS) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf070,
		    "qla_target(%d): Failed to retrieve fcport "
		    "information -- get_port_database() returned %x "
		    "(loop_id=0x%04x)", vha->vp_idx, rc, loop_id);
		kfree(fcport);
		return NULL;
	}

	return fcport;
}
