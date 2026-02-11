qla4xxx_queuecommand(struct Scsi_Host *host, struct scsi_cmnd *cmd)
{
	struct scsi_qla_host *ha = to_qla_host(host);
	struct ddb_entry *ddb_entry = cmd->device->hostdata;
	struct iscsi_cls_session *sess = ddb_entry->sess;
	struct srb *srb;
	int rval;

	if (test_bit(AF_EEH_BUSY, &ha->flags)) {
		if (test_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags))
			cmd->result = DID_NO_CONNECT << 16;
		else
			cmd->result = DID_REQUEUE << 16;
		goto qc_fail_command;
	}

	if (!sess) {
		cmd->result = DID_IMM_RETRY << 16;
		goto qc_fail_command;
	}

	rval = iscsi_session_chkready(sess);
	if (rval) {
		cmd->result = rval;
		goto qc_fail_command;
	}

	if (test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	    test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags) ||
	    test_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags) ||
	    !test_bit(AF_ONLINE, &ha->flags) ||
	    !test_bit(AF_LINK_UP, &ha->flags) ||
	    test_bit(AF_LOOPBACK, &ha->flags) ||
	    test_bit(DPC_POST_IDC_ACK, &ha->dpc_flags) ||
	    test_bit(DPC_RESTORE_ACB, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags))
		goto qc_host_busy;

	srb = qla4xxx_get_new_srb(ha, ddb_entry, cmd);
	if (!srb)
		goto qc_host_busy;

	rval = qla4xxx_send_command_to_isp(ha, srb);
	if (rval != QLA_SUCCESS)
		goto qc_host_busy_free_sp;

	return 0;

qc_host_busy_free_sp:
	qla4xxx_srb_free_dma(ha, srb);
	mempool_free(srb, ha->srb_mempool);

qc_host_busy:
	return SCSI_MLQUEUE_HOST_BUSY;

qc_fail_command:
	cmd->scsi_done(cmd);

	return 0;
}
