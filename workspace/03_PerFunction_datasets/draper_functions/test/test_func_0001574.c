qla2x00_process_completed_request(struct scsi_qla_host *vha,
				  struct req_que *req, uint32_t index)
{
	srb_t *sp;
	struct qla_hw_data *ha = vha->hw;


	if (index >= req->num_outstanding_cmds) {
		ql_log(ql_log_warn, vha, 0x3014,
		    "Invalid SCSI command index (%x).\n", index);

		if (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		else
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		return;
	}

	sp = req->outstanding_cmds[index];
	if (sp) {

		req->outstanding_cmds[index] = NULL;


		sp->done(ha, sp, DID_OK << 16);
	} else {
		ql_log(ql_log_warn, vha, 0x3016, "Invalid SCSI SRB.\n");

		if (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		else
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	}
}
