iscsit_handle_snack(
	struct iscsi_conn *conn,
	unsigned char *buf)
{
	struct iscsi_snack *hdr;

	hdr			= (struct iscsi_snack *) buf;
	hdr->flags		&= ~ISCSI_FLAG_CMD_FINAL;

	pr_debug("Got ISCSI_INIT_SNACK, ITT: 0x%08x, ExpStatSN:"
		" 0x%08x, Type: 0x%02x, BegRun: 0x%08x, RunLength: 0x%08x,"
		" CID: %hu\n", hdr->itt, hdr->exp_statsn, hdr->flags,
			hdr->begrun, hdr->runlength, conn->cid);

	if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
		pr_err("Initiator sent SNACK request while in"
			" ErrorRecoveryLevel=0.\n");
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	}


	switch (hdr->flags & ISCSI_FLAG_SNACK_TYPE_MASK) {
	case 0:
		return iscsit_handle_recovery_datain_or_r2t(conn, buf,
			hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_STATUS:
		return iscsit_handle_status_snack(conn, hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun), be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_DATA_ACK:
		return iscsit_handle_data_ack(conn, be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_RDATA:

		pr_err("R-Data SNACK Not Supported.\n");
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	default:
		pr_err("Unknown SNACK type 0x%02x, protocol"
			" error.\n", hdr->flags & 0x0f);
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	}

	return 0;
}
